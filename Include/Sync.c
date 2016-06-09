void pushSyncBuffer(char i){
    #asm("cli")
    syw_buffer[syw_wr_index++]=i;
    if (syw_wr_index == SYW_BUFFER_SIZE) syw_wr_index=0;
    syw_counter++;
    if (syw_counter == SYW_BUFFER_SIZE) {
        syw_counter = 0;
        syw_overflow=1;    
    }
    #asm("sei")
    if (syw_counter==1){
        sendNextSy();
    }                     
}
unsigned char readSyncBuffer(){
    return syw_buffer[syw_rd_index];    
}
void pullBuffer(){
    #asm("cli")
	++syw_rd_index;
    if (syw_rd_index == SYW_BUFFER_SIZE) syw_rd_index=0;
    --syw_counter;
    #asm("sei")  
}

void putchar(char c){
    while (tx_counter == TX_BUFFER_SIZE);
    #asm("cli")
    if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
    {
       tx_buffer[tx_wr_index++]=c;
       if (tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
       ++tx_counter;
    }
    else
    {
       UDR=c;
    }
    #asm("sei")
}
void sendNextSy(){
    unsigned char i,data;
    if(syw_counter!=0){
        i=readSyncBuffer();
        data=syReg[i];
        syw_chk = CREATE_ACK(i,data);
        putchar(0xff);
        putchar(i);
        putchar(data);
        StartTimer(TRANS_RESEND_TIMER,RESEND_T,sendNextSy);
    }
}

void setInterrupt(char n,void(*f)(char)){
	intFunc[n]=f;
}

#pragma warn-
void nop(char x){}
#pragma warn+ 
// Initialize ATmega32 UART register
void initSync(){
    char i;
    UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
    UCSRB=(1<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
    UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
    UBRRH=0x00;
    UBRRL=0x33;
    for (i=0;i<REG_SIZE;i++){
        setInterrupt(i,nop);
    }	
}

void setReadReg(char n,char data){
	syReg[n]=data;
    putchar(ACK_START);
    putchar(CREATE_ACK(n,data));
	SETI(n);
}

void RunInterrupts(){
	char i,j,n;
	for (i=0;i<(REG_BIT_SIZE);i++){
		if (iFlag[i]!=0){
			for (j=0;j<=7;j++){
				n=i*8+j;
				if (READI(n)){
					intFunc[n](syReg[n]);
					RESETI(n);
					return;
				}
			}
		}
	}
}

interrupt [USART_RXC] void usart_rx_isr(void)
{
    char status,data;
    status=UCSRA;
    data=UDR;
    if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
    {
        if (data==READ_START){
            read_reg_step=1; 
        }else if (read_reg_step==1){
            read_i=data;
            read_reg_step++;  
        }else if (read_reg_step==2){
			setReadReg(read_i,data);
            read_reg_step=0;
        }
        
        if (data==ACK_START){
            read_ack_step=1;
        }else if (read_ack_step==1){
            if (data==syw_chk){
                StopTimer(TRANS_RESEND_TIMER);
                pullBuffer();
                sendNextSy();    
            }
            read_ack_step=0;
        }
            
    }
}
interrupt [USART_TXC] void usart_tx_isr(void)
{
   if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index++];
   if (tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
   }
}

void WriteReg(unsigned char i,unsigned char data)
{
	while (syw_counter == SYW_BUFFER_SIZE);
	if(data>=0xfe)
		  data=0xfd;
	syReg[i]=data;
	pushSyncBuffer(i);
}