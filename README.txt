-----------------------------------------------------------------------------------------------------------LoRa Gateway con protocollo LoRaWAN--------------------------------------------------------------------------

														   --Ivano 24/08/2016--

----------------------INSTALLAZIONE----------------------

Prima di eseguire il gateway su una nuova raspberry eseguire lo script install.cmd

	 .../lorawan/Raspberry$ sudo ./install.cmd

Se si hanno problemi con l'esecuzione dello script digitare il seguente comando :

	 .../lorawan/Raspberry$ sudo chmod -x install.cmd

L'esecuzione dello script install.cmd provveder� all'installazione dei pacchetti linux necessari per il gateway

------> curl
------> libcurl4-gnutls-dev

Se i seguenti pacchetti sono gi� installati non ci sar� bisogno di fare niente, se invece  i pacchetti non sono installati premere 'Y' quando richiesto

Alla fine dell'installazione lo script provveder� alla compilazione del gateway e sucessivamente alla sua esecuzione. Se si volesse uscire dal gateway per delle configurazioni premere Ctrl+z

--------------------ESECUZIONE----------------------------

Per eseguire il gateway � sufficente eseguire lo script run.cmd

	.../lorawan/Raspberry$ sudo ./run.cmd 

Se si hanno problemi con l'esecuzione dello script digitare il seguente comando :

	.../lorawan/Raspberry$ sudo chmod -x run.cmd