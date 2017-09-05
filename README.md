
# Old outdated repository, here just for the memories, don't waste your time digging in here

---------------------------------------LoRa Gateway con protocollo LoRaWAN---------------------------------

						   --Ivano 24/08/2016--
				----------------------CONFIGURAZIONE---------------------

Ogni rete avrà un'identificativo diverso a 7 bit. Questo identificativo si può trovare nel file SX1272.h

#define NETWORK_ID 0x4D      // modificare 0x4D con l'identificativo di rete che si preferisce da
			     // 0 a 127 in esadecimale

!!ATTENZIONE!! Per evitare di intercettare pacchetti di altre reti ogni rete deve avere il suo NETWORK_ID unico

Ogni end-device presente nella rete ha un suo network address diverso a 25 bit. 
Questo identificativo si può trovare nel file SX1272.h

#define NETWORK_ADDRESS 0xC  // modificare 0xC con l'indirizzo in rete che si preferisce da 0 a (2^25 -1)

!!ATTENZIONE!! Per evitare confusione sul mittente e il rischio di perdere messaggi ACK ogni end-device 
(raspberry compreso) deve avere il suo NETWORK_ADDRESS unico 
Due end-device su due reti diverse possono avere NETWORK_ADDRESS uguale.

Nota : perchè un raspberry riceva dei messaggi dagli arduini è necessario che il raspberry e gli arduini 
che fanno riferimanto a lui abbiano lo stesso NETWORK_ID
 
----------------------INSTALLAZIONE----------------------

Prima di eseguire il gateway su una nuova raspberry eseguire lo script install.cmd

	 .../lorawan/Raspberry$ sudo ./install.cmd

Se si hanno problemi con l'esecuzione dello script digitare il seguente comando :

	 .../lorawan/Raspberry$ sudo chmod 777 install.cmd

L'esecuzione dello script install.cmd provvederà all'installazione dei pacchetti linux necessari per il gateway

------> curl
------> libcurl4-gnutls-dev

Se i seguenti pacchetti sono già installati non ci sarà bisogno di fare niente
Se invece  i pacchetti non sono installati premere 'Y' quando richiesto

Alla fine dell'installazione lo script provvederà alla compilazione del gateway e sucessivamente alla sua
esecuzione. Se si volesse uscire dal gateway per delle configurazioni premere Ctrl+z

--------------------ESECUZIONE----------------------------

Per eseguire il gateway è sufficente eseguire lo script run.cmd

	.../lorawan/Raspberry$ sudo ./run.cmd 

Se si hanno problemi con l'esecuzione dello script digitare il seguente comando :

	.../lorawan/Raspberry$ sudo chmod 777 run.cmd
