# AAAReserve stablecoin for EOS mainnet
AAAreserve is a stablecoin for the EOS mainnet backed by a basket of FIAT currencies. 

## Objective
AAAReserve is designed to be a community lead stablecoin, providing a usable stable currency that is easily redeemable into FIAT. By deploying AAAReserve on EOS mainnet we not only provide a stable coin to the community but also due to the speed and cost of transactions we create a coin that becomes usable as a real world currency.

### Not a peg
AAA Reserve is not a peg to another currency. Its value is derived from cash held in a basket of currencies. This means that AAA Reserve is stable across multiple currencies rather than just a single one.

### Not for profit
AAA Reserve is not a profit-seeking stablecoin. Its sole purpose is to serve as a stable-valued coin. Nothing else. 

### Regulation
AAA Reserve was the first stablecoin to be signed off by a regulator, in 2017. We are pleased to see others following our lead.

### Stability
Coins can always be purchased or sold through AAAReserve.com at the NAV price featured on the site. The NAV price is calculated based on the value of the basket of currencies, details of this can be seen on <a href="http://www.AAAReserve.com">www.aaareserve.com/nav</a>. This ability to easily purchase and liquidate means that speculation on an exchange would be pointless as the currency can always be purchased at NAV price.

For a detailed overview please visit <a href="https://www.AAAReserve.com">AAAreserve.com</a>. For our original whitepaper on how the coin operates and NAV is calculated read our <a href="https://www.aaareserve.com/arc-reserve-documentation">whitepaper</a>

## Technical Overview

The AAAReserve currency has two components. The smart contract that features in this repository and the AAAReserve website and administration system.

### AAAReserve.com and administration system  

Amounts of currencies held both in investments and cash are recorded in the administration system. The values of these are displayed on the NAV page on AAAReserve.com and used to calculate the NAV rate ( see the <a href="https://www.aaareserve.com/arc-reserve-documentation">whitepaper</a> for more detail on the NAV calculations ). 

Issuing or burning of coins is only permitted when the FIAT balances are increased by a deposit or a withdrawal from the accounts, this process is completed through AAAReserve.com.

Users can purchase AAA Reserve through the AAAReserve.com website using FIAT. Once a user has completed AML checks they are asked to wire the funds to the bank account appropriate to the currency.
Once the funds are received, the administration system is updated with the new values from the bank accounts, the maximum number of allowed coins in circulation is then increased by calling the setmaxsupply() function on the AAAReserve EOS Contract, with the new values of permitted coins in circulation. The issue() function is then called to mint and transfer the new coins to the users account in question.

### Smart Contract

The smart contract featuring in this repository is based on eosio.token code. It has been altered to allow the changing of the max_supply value which represents the maximum number of tokens allowed in circulation and the burning of tokens to remove them from circulation. This change makes the operation of the stable coin possible by allowing the permitted circulation to vary in line with the assets held that back it, in this case the basket of currency. As such it has the addition of 2 new funcitons over the original contract setmaxsupply() and burn().

Once created the following command creates the AAA reservetoken with a maximum circulation of 1.0000 AAA.
```sh
cleos push action reservetoken create '["reservetoken","1.0000 AAA"]' -p reservetoken
```
The following call increases the permitted circulation to 100,000 AAA.
```sh
cleos push action reservetoken setmaxsupply '["100000.0000 AAA"]' -p reservetoken
```
The following call mints and transfers 100,000 AAA to aaaexamplecc
```sh
cleos push action reservetoken issue '["aaaexampleac","100000.0000 AAA","new coins"]' -p reservetoken
```
The following call transfers 1,000 AAA back to the contract owner account.
```sh
cleos push action reservetoken transfer '["aaaexampleac","reservetoken","1000.0000 AAA","back for burn"]' -p reservetoken
```
The following call reduces the permitted circulation to 99,000 AAA allowing us then to burn.
```sh
cleos push action reservetoken setmaxsupply '["99000.0000 AAA"]' -p reservetoken
```
The following call burns the transferred 1,000 AAA from the contract owner account.
```sh
cleos push action reservetoken burn '["1000.0000 AAA"]' -p reservetoken
```
