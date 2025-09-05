global defaultISR

defaultISR:
    pusha
    cli
    
    hlt ; TODO-> implement a regular ISR 
    
    popa
    ret
