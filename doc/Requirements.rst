=============================================
Ticket vending machine project - requirements
=============================================

Description
-----------
The vending machine gets/charges calculated amount of money, and then the machine gives the tickets and the rest of the money.
It is possible to buy several tickets at once, pay whole amount of money and then get all the tickets.
 

Product requirements
--------------------
The vending machine must be able to accept various available coins - both złote and grosze.
The machine must sell tickets taking into account transport zones or reduced/half-price tickets.
The vending machine always gives change using the largest available denominations, which is equivalent to giving change using the smallest possible number of coins.


Project requirements
--------------------
- At least one lambda function must be used.
- Any smart pointer must be used.
- At least one STL container must be used.
 

Boundary conditions
-------------------
Boundary conditions must be taken into account, in example (for example, they do not necessarily have to be like this):
- lack of paper to print the ticket
- no coins to give change
 

User Interface
--------------
- Any simple User Interface must be implemented - even a text UI.
 

Tests
-----
- If possible, some simple Unit tests must be implemented - it could be, but not necessarily, used any testing framework.
 

Environment
-----------
- The programming environment does not matter, but there should be the instructions on how to build and run the project.


Additional points for
---------------------
- Using proper design patterns
- Sticking to SOLID rules
- Making the vending machine code easily extendable for future use with different currencies


Additional information
----------------------
If you have any questions or doubts about the requirements and the task, please feel free to contact us 😊
