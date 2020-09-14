
uint8_t btn_pin= B00000100; //4
uint8_t led_pin= B00000010; //2
uint8_t btn_interrupt_pin= B00000011; //3
//btn_state=>
volatile uint8_t toggle_led =0; //LOW 

void setup() {
                 // pinMode(btn, INPUT_PULLUP);
                 // pinMode(led, OUTPUT);
                 // pinMode(btn_interrupt_pin, INPUT_PULLUP);
    ///INPUT= 0
    ///OUTPUT=1
DDRD=   B00000110; //bit0=> rx  DDR1= INPUT
                    ///bit1=> tx  DDR1= OUTPUT
                   ///bit2=> pin DDR2= led OUTPUT
                   //bit3=> to je za interrupt_btn_pin i settano je dolje niÅ¾e             
                   //bit4=> pin DDR4= btn 
PORTD=  B00010000; ///bit4=>  DD4= INPUT_PULLUP resistor ukljucen

//bit3=> DDR3= INTERRUPT btn input
 DDRD &= ~(1<<btn_interrupt_pin); // da mu bude 0 na tom mjestu- INPUT
 PORTD |= (1<<btn_interrupt_pin); // stavljam pullup resistor  
 //Stavim interrupt handler, (  pin(D2 ili D3) , InterrruptServiceRoutine_funkcija kratka, LOW/CHANGE/FALLING/RISING  )
attachInterrupt(digitalPinToInterrupt(btn_interrupt_pin), ISR_btn_push, LOW);
}
void loop() {
//oÄitavam stanje na gumbu koji je u strujnom krugu s lampicom 
toggle_led = (PIND & (1<<btn_pin))>>btn_pin; // btn_press = digitalRead(btn);

if (toggle_led == 0){
  PORTD= PORTD | (1<<led_pin); //digitalWrite(led_pin, HIGH);
}
else{
  PORTD &= ~(1<<led_pin); //digitalWrite(led_pin, LOW);
  }
}
void ISR_btn_push(){
  //mijenjam stanje gumbom koji nije u krugu s lampicom
    toggle_led=~toggle_led;
 }
