void read_keyboard(){

while(1)
{
    switch( uart_getc() ){

    case 1:
        putc( 1 );
        break;

    default:
        break;
    }


}
}
