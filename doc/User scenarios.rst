User scenarios

#1 User scenarios - 1 Client, 1 ticket, 1 zone, full price, exact money for ticket (no change)

Input:
    Machine contain conis to return change.
    Client select 1 ticket from 1 zone with "full" price.
    On console there is information about full price to pay.
    Client put exact amount of money into machine.

Expected output:
    Client get 1 selected ticket.
    Machine has (-1) empty tickets and additional money from Client.


#2 User scenarios - 1 Client, 1 ticket, 1 zone, full price, more money than price (change expected)

Input:
    Machine contain conis to return change.
    Client select 1 ticket from 1 zone with "full" price.
    On console there is information about final price to pay.
    Client put into machine more money that final price.

Expected output:
    Client get 1 selected ticket and change from machine in lowest possible amount of coins/papers.
    Machine has (-1) empty tickets, additional money from Client and (- return change) money.


#3 User scenarios - 1 Client, 3+2 tickets, 2 types, full+reduced price, more money than price (change expected)

Input:
    Machine contain conis to return change.
    Client select 3 tickets from 1 zone with "full" price.
    Client select additional 2 tickets from 2 zone with "reduced" price.
    On console there is information about final price to pay.
    Client put into machine more money that final price.

Expected output:
    Client get 5 selected tickets and change from machine in lowest possible amount of coins/papers.
    Machine has (-5) empty tickets, additional money from Client and (- return change) money.


#4 User scenarios - no change, client accept exact money only


#5 User scenarios - activation Admin account, terminating Machine


#6 User scenarios - activation Admin account, add coins/papers


#7 User scenarios - activation Admin account, add empty tickets

