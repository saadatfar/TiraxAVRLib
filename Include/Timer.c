//Run all timer functions
void RunTimer(){
    unsigned char i;
    for (i=0;i<TimerN;i++){
        if (READF(i)==1){
            tfunc[i]();
            RESETF(i);
            return;
        } 
    }
}
//Initialize ATmega32 Timer Registers
void initTimer(){
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
    TCNT0=0x83;
    OCR0=0x00;
    TIMSK=TIMSK | (1<<TOIE0); 
}