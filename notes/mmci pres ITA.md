# Titolo
Buon pomeriggio, sono Rocco Suanno ed oggi presento la mia tesi magistrale dal titolo "Control of phase separating systems close to criticality"

# Struttura
Inizierò spiegando il significato del titolo e quindi presentando l'obiettivo della tesi.

# Sistemi che separano fasi
Cos'è un sistema phase separating?
Per spiegare questo, dobbiamo considerare sistemi che possono essere descritti da un parametro d'ordine **scalare**.
Un esempio è il modello di Ising, dove è possibile definire in ogni punto la **magnetizzazione** facendo una media locale degli spin. E questo campo indica se gli spin in una certa regione sono allineati fra loro o meno.
Considerando invece una superficie **piana** (quella nera) sulla quale è possibile depositare al più uno strato di atomi, si può definire una densità di siti della superficie coperti.

Diciamo che il sistema è phase separating se **in origine** c'è solo uno stato stabile, che chiamiamo fase **omogenea**, siccome il parametro d'ordine è zero ovunque salvo piccole fluttuazioni. Successivamente, portando la temperatura al di sotto di un valore critico, questo stato diventa instabile e compaiono due nuovi stati stabili. Quindi, il sistema passa dalla fase omogenea alle due nuove fasi stabili, portando alla formazione di domini in cui il parametro d'ordine è +1 o -1.

Questo fenomeno è chiamato decomposizione spinodale e, dal potenziale sulla destra, si vede che una piccola perturbazione è sufficiente per innescare la transizione di fase. Perciò si oserva questo pattern **interconnesso**, tipico della decomposizione spinodale.

# Vicino alla criticità
Vogliamo studiare questo tipo di sistemi vicino alla temperatura critica.
La ragione si chiama **universalità** e indica che sistemi apparentemente molto diversi mostrano lo stesso comportamento vicino al punto critico.
Ad esempio, qui abbiamo una **sospensione colloidale**: ovvero ci sono molte sfere nanometriche in un liquido. All'inizio viene agitata, quindi si ha una miscela omogenea. Poi viene lasciata a riposo e si verifica una separazione di fase, dove la fase più chiara ha una concentrazione maggiore di queste piccole sfere. Abbiamo poi una simulazione Monte Carlo del modello di Ising. In entrambi i casi, vediamo l'emergere di un pattern interconnesso, tipico della decomposizione spinodale.

# Controllo
Ora che abbiamo presentato la **classe** di sistemi di nostro interesse, qual è il nostro obiettivo?
Il nostro obiettivo è capire **come** controllare la posizione, la forma e la dimensione di questi domini variando la temperatura nel tempo.

# Riepilogo
Per essere chiari, siamo interessati all'intera classe di sistemi che presentano una decomposizione spinodale quando la temperatura scende sotto un valore critico. E vogliamo controllare le proprietà del sistema variando la temperatura **attorno al valore critico**.

# TDGL
Per questi sistemi, esiste un modello ben noto che descrive la dinamica vicino alla temperatura critica.
Si tratta dell'equazione di Ginzburg-Landau dipendente dal tempo e dipende da un parametro C, che quantifica quanto siamo lontani dal punto critico. E questo parametro ha una dipendenza temporale, se variamo la temperatura nel tempo. Questa equazione descrive bene la dinamica osservata in una simulazione Monte Carlo del modello di Ising, così come il sistema sulla destra. Sulla destra è rappresentato un mono-layer, quindi abbiamo un substrato (la parte nera) che può essere coperto con al più uno strato di atomi.

-----------------

Gli atomi in un gas sovrastante possono legarsi al substrato e rimanere lì, oppure possono perdere un legame e tornare nella fase gassosa. Questo meccanismo porta alla stessa dinamica della simulazione a sinistra ed è quindi ben descritto dal modello.

------------------

Cosa sappiamo di questa equazione?
In letteratura, questa equazione è stata studiata principalmente quando la temperatura è mantenuta costante nel tempo, quindi il parametro C **è fissato**. Mentre poco si sa del caso in cui C ha una dipendenza temporale.
Vediamo la dinamica nel regime in cui C è fisso.

# Instabilità lineare

Consideriamo uno stato iniziale in cui la magnetizzazione è una piccola perturbazione di zero, come nell'immagine a sinistra. Poiché la perturbazione è piccola, l'effetto del termine cubico è trascurabile e abbiamo un'equazione lineare. Risolvendola, troviamo che i modi del sistema hanno una dipendenza dal tempo esponenziale, con una velocità di crescita C-q^2. Questo è un grafico della velocità di crescita in funzione del momento q del modo di Fourier. Quando la funzione è positiva, significa che il modo cresce, mentre se è negativa decade a zero. E poiché la lunghezza d'onda di un modo è il reciproco di q, i modi che crescono hanno un q basso, quindi una lunghezza d'onda grande. Mentre i modi a lunghezza d'onda piccola si attenuano.

Ora questa crescita aumenta l'ampiezza della perturbazione e quindi il termine cubico non è più trascurabile.

# Dinamica non lineare
Non appena il termine cubico diventa rilevante, si ha una competizione tra due effetti, dovuti al termine lineare Cm e a quello non lineare $m^3$. In ogni punto del sistema, il termine lineare spinge il campo m verso più infinito o meno infinito, mentre quello cubico, a causa del segno meno, lo spinge verso zero. Questa competizione porta il campo a due valori di equilibrio **opposti**, che corrispondono ai minimi del potenziale a doppia buca. Quindi raggiungiamo uno stato in cui il parametro d'ordine è costante in certi intervalli, che chiamiamo domini, mentre chiamiamo le interfacce tra domini kink, se il campo decresce, o anti-kink se aumenta.

Qui ho riportato un profilo 1D, ma tutte le idee che ho presentato finora sono valide anche in 2 dimensioni. Ciò che dipende dalla dimensione è il movimento delle interfacce.

# Dinamica 1D
In un sistema mono-dimensionale, le interfacce si chiamano kink e antikink, perché si attraggono debolmente, con un'interazione che decresce esponenzialmente con la distanza. E una volta che si incontrano, si annichilano, con un tempo di annichilazione che cresce esponenzialmente con la distanza. Quindi questa dinamica è molto lenta. Ma in 2D esiste un altro meccanismo che domina su questa debole interazione.

# Dinamica 2D
Questo è chiamato **motion by curvature** e significa che se consideriamo un'interfaccia tra domini, che qui è ingrandita, ogni punto dell'interfaccia si muove con una velocità normale all'interfaccia e proporzionale alla curvatura locale. Dove la curvatura kappa è definita considerando la circonferenza tangente all'interfaccia nel punto considerato e prendendo il reciproco del suo raggio.

# Coarsening
Entrambi i meccanismi portano a una dinamica **globale** nota come coarsening. Questo significa che la grandezza tipica dei domini aumenta nel tempo.

Questi grafici mostrano la grandezza dei domini in funzione del tempo.
In 1D, la debole interazione tra kink porta la dimensione dei domini ad aumentare **molto lentamente**, come il logaritmo del tempo. Quindi la dimensione dei domini appare costante in questa simulazione. Mentre in 2D, il motion by curvature produce una dinamica **più veloce**, in cui la dimensione dei domini cresce come una potenza del tempo.

-----------------------------------

Quello che ho mostrato finora è la dinamica a **temperatura costante**, quindi quando il parametro **C è fisso**. Invece, ci siamo chiesti:
"Cosa succede se C ha una dipendenza temporale?"
"Possiamo controllare la forma dei domini scegliendo opportunamente la forma di C(t)?"

# C(t) come oscillazione
In particolare, ci siamo chiesti se è possibile ottenere questo controllo facendo oscillare C intorno a un valore medio Cbar.
Quindi ora presenterò come **questa** oscillazione di C influisce sulla dinamica che ho mostrato prima.

# Dinamica lineare
Iniziamo chiedendoci come viene influenzata la dinamica lineare. 
Ricordo che se partiamo da uno stato che è una piccola perturbazione di zero, il termine cubico nell'equazione è trascurabile e quindi la dinamica iniziale è lineare. I modi a lunga lunghezza d'onda crescono esponenzialmente, mentre i modi a corta lunghezza d'onda si attenuano.

 Ciò che cambia ora è che, invece di avere C nella velocità di crescita, ora abbiamo la sua media temporale.

Per studiare come l'oscillazione di C influisce sulla dinamica lineare, abbiamo calcolato il momento quadrato medio dei modi di Fourier, pesato sulla loro ampiezza. E abbiamo utilizzato questo valore per definire l, che è una lunghezza caratteristica del sistema, **nel senso che** descrive la **dimensione delle caratteristiche** del sistema. Abbiamo scoperto che questa lunghezza cresce secondo una legge di potenza durante la dinamica lineare e questa crescita non dipende da come si varia C nel tempo.

Ma cosa succede alla dinamica non lineare? 
Procederò passo dopo passo, considerando cosa accade a ogni dimensione, da 0 a 2.

# 0D
Partiamo da un sistema 0 dimensionale, il che significa che lo stato iniziale è omogeneo nello spazio, quindi non ci sono derivate spaziali nell'equazione.

In questo caso, possiamo risolverlo analiticamente e abbiamo trovato che:
- Se Cbar è diverso da zero, si osserva una convergenza esponenzialmente rapida
- Invece, il caso in cui Cbar è uguale a zero è speciale e porta a un decadimento secondo una legge di potenza.

# 1D
Nel caso 1D, conosciamo la forma dei kink e come interagiscono nel caso in cui C è fisso. Ma cosa succede se facciamo oscillare C nel tempo?

-----------

Abbiamo usato un approccio perturbativo, chiamato espansione su più scale, per studiare come un'oscillazione di C influenza la dinamica. Abbiamo studiato due casi limite: quando le variazioni di C sono lente o veloci. In entrambi i casi, si può definire un piccolo parametro epsilon, come il reciproco del periodo o il periodo. Così abbiamo potuto **espandere la dinamica** in questo piccolo parametro.

Abbiamo scoperto che, al primo ordine, il movimento del kink non è influenzato da come C oscilla. Tuttavia, la forma dei kink cambia.

Nel limite veloce, la nostra espansione non fornisce la correzione alla forma del kink. Mentre nel limite lento possiamo calcolare la correzione al primo ordine. Abbiamo calcolato sia l'ampiezza della correzione beta, in funzione del tempo, sia la forma della correzione uk. A destra, la correzione che abbiamo calcolato per la forma del kink (in rosso) è confrontata con la deviazione massima dalla forma del kink che vediamo nelle simulazioni.

# 2D
Rimane ora il caso 2D, in cui la dinamica è governata dal movimento per curvatura. Anche qui abbiamo studiato i limiti in cui le oscillazioni di C sono lente o veloci e anche qui il movimento delle interfacce tra domini non è influenzato dalle oscillazioni. Quindi non si può controllare la posizione e la forma dei domini introducendo oscillazioni della temperatura. **Devo dire che, nella nostra analisi, abbiamo assunto che le oscillazioni fossero strettamente positive. Cioè, mantenendo la temperatura al di sotto del valore critico. Quindi non sappiamo ancora se questo sia un risultato generale o meno.**

Abbiamo anche verificato numericamente questo risultato.
Abbiamo considerato un dominio circolare isolato il cui raggio quadrato, se il movimento per curvatura **vale**, dovrebbe decadere linearmente nel tempo. Qui abbiamo due simulazioni in cui le oscillazioni di C sono lente o veloci e possiamo vedere il decadimento previsto.

Quindi vediamo che l'introduzione di oscillazioni di C non influisce né sulla dinamica lineare né sul movimento per curvatura.

# Dimensione dei domini (2D)
In generale non influisce sulle proprietà del sistema.
Infatti, qui abbiamo due lunghezze caratteristiche del sistema.
Quella a sinistra è stata definita prima ed è ispirata al fatto che ogni modo di Fourier ha una lunghezza d'onda di 2pi su q.
Questa descrive la dimensione tipica delle caratteristiche del sistema e si prevede che aumenti secondo una legge di potenza nel regime lineare, dove l'ampiezza di ogni modo è ancora piccola.
Mentre la quantità a destra è l'area del sistema divisa per la lunghezza totale dell'interfaccia. Questa descrive la dimensione dei domini e si prevede che cresca secondo una legge di potenza nel regime non lineare, dove il movimento per curvatura guida la dinamica.
Il caso in cui C è fisso è confrontato con il caso in cui C oscilla. E possiamo vedere che c'è una buona corrispondenza anche a lungo termine, durante il regime non lineare.

# Principali risultati
Cosa possiamo controllare modulando C nel tempo?

In 2D non possiamo controllare la **dimensione** dei domini, perché aumenta nel tempo a causa del movimento per curvatura e non c'è modo di fermare questo meccanismo modulando C nel tempo. Invece, in 1D la dinamica non lineare è molto lenta e quindi la dimensione dei domini può essere considerata congelata.
Anche se la dinamica lineare è indipendente da C, la **durata dell'approssimazione lineare** dipende da C!
Quindi puoi modulare C in modo da selezionare la dimensione dei domini alla fine del regime lineare. Poi la dinamica è così lenta che puoi assumere che i domini mantengano **quella** dimensione.

# Conclusioni
In conclusione, abbiamo studiato come controllare l'equazione di Ginzburg-Landau dipendente dal tempo variando la temperatura al di sotto del valore critico.
Abbiamo scoperto che l'unica proprietà che possiamo controllare in questo modo è la dimensione dei domini in 1D e questo è coerente con i risultati di un precedente progetto che ha studiato questo problema con il machine learning.
Poi, ci siamo concentrati solo sul caso in cui l'oscillazione di C è strettamente positiva.
Tuttavia, abbiamo visto nelle simulazioni che con un'oscillazione più generale C accelera l'avvicinamento dei kink, permettendo un ulteriore controllo della dimensione dei domini in 1D.
Sebbene siano necessarie ulteriori indagini per comprendere teoricamente questo fenomeno.