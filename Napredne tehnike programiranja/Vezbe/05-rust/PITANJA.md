# V5 - Programski jezik Rust

## Pametni pointeri, kolekcije

1. Šta predstavlja pointer?
    -Definicija: Pointer je promenljiva koja sadrži memorijsku adresu, tj. lokaciju u memoriji gde je smeštena vrednost neke druge promenljive.
    Praktična primena: Pointeri omogućavaju efikasno manipulisanje memorijom i referenciranje podataka.
2. Koji je najčešća vrsta pointera u Rust-u?
    - U Rust-u, najčešća vrsta pointera je borrow checker (pozajmica), koja se koristi uz reference (&T i &mut T). Ovaj mehanizam omogućava sigurnu i efikasnu upotrebu memorije bez potrebe za ručnim upravljanjem resursima.
3. Šta predstavlja pametni pointer (Engl. smart pointer)?
    - Definicija: Pametni pointer je objekat koji, pored memorijske adrese, često sadrži i dodatne informacije i funkcionalnosti (npr. broj referenci, automatizovano oslobađanje memorije, itd.).
Praktična primena: Pametni pointeri pomažu u upravljanju resursima na apstraktan način, često uz dodatnu funkcionalnost koja olakšava rad programera.
4. Koja je glavna razlika između pametnog pointera i reference?
    - Perfomanse su im slicne, ali pametni pojnteri alociraju memoriju na hipu.
    - Reference u Rust-u se koriste kroz borrow checker i ne omogućavaju vlasništvo podataka. Mogu biti &T za pozajmicu ili &mut T za promenljivu pozajmicu.
Pametni pointeri (npr. Box<T>, Rc<T>, Arc<T>) imaju vlasništvo nad podacima i omogućavaju dodatne funkcionalnosti, poput deljenja vlasništva ili praćenja broja referenci.
5. Da li su `String` i `Vec<T>` pametni pointeri?
    - Da, String i Vec<T> su vrste pametnih pointera. String je pametni pointer koji poseduje nisku (string), dok Vec<T> poseduje dinamički niz vrednosti tipa T.
6. Preko čega se pametni pointeri obično implementiraju?
    - Pametni pointeri se često implementiraju preko struktura i implementacija određenih trеjta (traits) koji definišu njihovo ponašanje (npr. Deref, Drop, Clone).
7. Šta predstavlja `Box<T>`?
    - efinicija: Box<T> je pametni pointer koji pruža vlasništvo nad vrednošću tipa T na heap memoriji.
Praktična primena: Koristi se kada želimo jasno definisano vlasništvo nad podacima i kada želimo da oslobodimo memoriju čim Box<T> izađe iz opsega.
    - Podaci se cuvaju na hipu.
8. U kojim situacijama se koristi `Box<T>`?
    - Box<T> se često koristi kada želimo alocirati vrednost na heapu, a da ne gubimo jasno definisano vlasništvo. Takođe, koristi se kada imamo strukturu ili enumeraciju koja treba da bude deo drugih struktura, a veličina nije poznata u vreme kompilacije.
Primer: let boxed_integer: Box<i32> = Box::new(42);
9. Da li sledeći kod proizvodi grešku? Zašto? Više detalja o `Cons` listi na sledećem [linku](https://doc.rust-lang.org/book/ch15-01-box.html#more-information-about-the-cons-list).

    ```rust
    enum List {
        Cons(i32, List),
        Nil,
    }

    use crate::List::{Cons, Nil};

    fn main() {
        let list = Cons(1, Cons(2, Cons(3, Nil)));
    }
    - Proizvodi je. Razlog tome je sto je velicina List tipa beskonacna. Kompajler predlaze upotrebu indirekcije kroz Box
    ```

10. Ispravi grešku u prethodnom kodu upotrebom `Box<T>`.
enum List {
    Cons(i32, Box<List>),
    Nil,
}

use crate::List::{Cons, Nil};

fn main() {
    let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
}
11. Koja je uloga `Deref` osobine?
Deref (od "dereference") je Rust osobina (trait) koja definiše ponašanje prilikom dereferenciranja vlasnika podataka. Tačnije, Deref omogućava implementaciju funkcije deref, koja se poziva kada se koristi operator dereferenciranja (*). Ovo je korisno za pristupanje vrednostima unutar pametnih pointera ili drugih tipova koji implementiraju ovu osobinu.
Implementacijom ove osobine proizvoljni tipovi se mogu tretirati kao reference.
Na primer, ako imamo strukturu koja sadrži pametni pointer, možemo implementirati Deref kako bismo olakšali rad sa vrednostima unutar tog pametnog pointera. Evo jednostavnog primera:
use std::ops::Deref;

struct MyBox<T> {
    data: T,
}

impl<T> MyBox<T> {
    fn new(data: T) -> MyBox<T> {
        MyBox { data }
    }
}

// Implementacija Deref za MyBox
impl<T> Deref for MyBox<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        &self.data
    }
}

fn main() {
    let my_box = MyBox::new(42);

    // Korišćenje operatora dereferenciranja (*)
    println!("Value inside MyBox: {}", *my_box);
}

12. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
        let x = 5;
        let y = &x;

        assert_eq!(5, x);
        assert_eq!(5, y);
    }

       fn main() {
        let x = 5;
        let y = &x;

        assert_eq!(5, x);
        assert_eq!(5, *y);
    }
    ```

13. Koja je razlika između prethodnog koda i sledećeg koda?

    ```rust
    fn main() {
        let x = 5;
        let y = Box::new(x);

        assert_eq!(5, x);
        assert_eq!(5, *y);
    }
    ```
    Razlika između ova dva dela koda leži u tome kako su vlasništvo i pozajmice upravljani u Rust-u.
        U suštini, prvi primer koristi vlasništvo pametnog pointera (Box<T>), dok drugi koristi pozajmicu (reference). Odabir između ovih zavisi od potreba i zahteva problema koji se rešava.

14. Šta predstavlja `struct MyBox<T>(T);`?
    -Definicija struct MyBox<T>(T); predstavlja deklaraciju generičke strukture (struct) u programskom jeziku Rust. Ova struktura se zove MyBox, a koristi se generički tip T. Struktura ima jedan polje koje ima isti tip T.

    Specifičnost ovde je u tome što je konstruktor MyBox definisan kao torka sa jednim elementom ((T)), što je ustvari kratka sintaksa za definisanje struktura sa jednim poljem. Dakle, MyBox se sastoji od jednog polja koje može biti bilo kojeg tipa.

15. Ispravi grešku u sledećem kodu implementiranjem `Deref` osobine:

    ```rust
    struct MyBox<T>(T);

    impl<T> MyBox<T> {
        fn new(x: T) -> MyBox<T> {
            MyBox(x)
        }
    }


    fn main() {
        let x = 5;
        let y = MyBox::new(x);

        assert_eq!(5, x);
        assert_eq!(5, *y);
    }
            struct MyBox<T>(T);
        use std::ops::Deref;
        impl<T> MyBox<T> {
            fn new(x: T) -> MyBox<T> {
                MyBox(x)
            }
        }
        impl<T> Deref for MyBox<T>{
            type Target = T;
            fn deref(&self) -> &Self::Target{
                &self.0
            }
        }

        fn main() {
            let x = 5;
            let y = MyBox::new(x);

            assert_eq!(5, x);
            assert_eq!(5, *y);
        }


    ```

16. Šta predstavlja `Deref` koercija?
    - Deref коерција представља имплицитну конверзију референци на тип који имплементира Deref у референцу на његов Target тип приликом позива функција и метода.
    Додато у језик да програмери не би морали да пишу превише експлицитних референцирања и дереференцирања.
    На пример, тип &String se имплицитно конвертује у &str
17. Pojednostavi poziv `hello` funkcije u sledećem kodu:

    ```rust
    struct MyBox<T>(T);

    impl<T> MyBox<T> {
        fn new(x: T) -> MyBox<T> {
            MyBox(x)
        }
    }

    use std::ops::Deref;

    impl<T> Deref for MyBox<T> {
        type Target = T;

        fn deref(&self) -> &Self::Target {
            &self.0
        }
    }

    fn hello(name: &str) {
        println!("Hello, {name}!");
    }

    fn main() {
        let m = MyBox::new(String::from("Rust"));
        hello(&(*m)[..]);
    }

    fn main() {
        let m = MyBox::new(String::from("Rust"));
        hello(&m);
    }
    ```

18. Kako se `Deref` koercija odnosi prema promenljivositi (Eng. mutability)? Za više informacija pročitati sledeću [sekciju](https://doc.rust-lang.org/book/ch15-02-deref.html#how-deref-coercion-interacts-with-mutability) knjige.
    -Deref koercija u Rust-u igra ključnu ulogu kada se radi o promenljivosti (mutability). Kada imamo referencu na vlasnika vrednosti (npr. &T ili &mut T), Rust može automatski primeniti Deref koerciju da bi nam omogućio pristup metodi ili funkciji koja očekuje vlasnika podataka, čak i ako imamo samo referencu na taj vlasnik.

    Promenljivost se odnosi na to da li referenca omogućava menjanje vrednosti koju referiše. Ako imamo referencu &T, to je nepromenljiva referenca, dok je &mut T promenljiva referenca koja omogućava menjanje vrednosti.

    Kada imamo vlasničku vrednost T i želimo pristupiti metodama ili funkcijama koje očekuju vlasničku vrednost, Rust automatski primenjuje Deref koerciju na referencu.
    Rust does deref coercion when it finds types and trait implementations in three cases:

        From &T to &U when T: Deref<Target=U>
        From &mut T to &mut U when T: DerefMut<Target=U>
        From &mut T to &U when T: Deref<Target=U>
     Rust will also coerce a mutable reference to an immutable one. But the reverse is not possible: immutable references will never coerce to mutable references. Because of the borrowing rules, if you have a mutable reference, that mutable reference must be the only reference to that data (otherwise, the program wouldn’t compile). 
19. Koja je uloga `Drop` osobine?
    Drop je Rust osobina (trait) koja definiše ponašanje kada vlasnički resurs biva oslobađan, odnosno kada vlasnički objekat izlazi iz opsega. 
    - Ако тип имплементира Drop тада ће компајлер позвати drop методу приликом изласка вредности из опсега важења.
    На пример, Box<T> имплементира Drop да би деалоцирао хип меморију приликом изласка из опсега важења.
20. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    struct CustomSmartPointer {
        data: String,
    }

    impl Drop for CustomSmartPointer {
        fn drop(&mut self) {
            println!("Dropping CustomSmartPointer with data `{}`!", self.data);
        }
    }

    fn main() {
        let c = CustomSmartPointer {
            data: String::from("my stuff"),
        };
        let d = CustomSmartPointer {
            data: String::from("other stuff"),
        };
        println!("CustomSmartPointers created.");
    }
    CustomSmartPointers created.
    Dropping CustomSmartPointer with data `other stuff`!
    Dropping CustomSmartPointer with data `my stuff`!
    ```

21. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    struct CustomSmartPointer {
        data: String,
    }

    impl Drop for CustomSmartPointer {
        fn drop(&mut self) {
            println!("Dropping CustomSmartPointer with data `{}`!", self.data);
        }
    }

    fn main() {
        let c = CustomSmartPointer {
            data: String::from("my stuff"),
        };
        let d = CustomSmartPointer {
            data: String::from("other stuff"),
        };
        drop(d);
        println!("CustomSmartPointers created.");
    }
    Dropping CustomSmartPointer with data `other stuff`!
    CustomSmartPointers created.
    Dropping CustomSmartPointer with data `my stuff`!
    ```

22. Da li postoji deljeno vlasništvo u Rust-u? Ako postoji, kako se realizuje?
    - Da, deljeno vlasništvo u Rust-u se postiže pomoću Rc<T> (Reference Counted) pametnog pointera. Rc<T> omogućava više vlasnika za isti resurs, ali ne dozvoljava menjanje resursa posle kreiranja.
23. Da li je `Rc<T>` siguran u kontekstu niti (Engl. threadsafe)?
    - Rc<T> nije threadsafe jer ne implementira Send trait, što znači da ne može automatski biti prenet između niti. Ako želite deljeno vlasništvo između niti, možete koristiti Arc<T> (Atomic Reference Counted), koji je threadsafe varijanta Rc<T>.
24. Da li `Rc::clone` obavlja duboko kopiranje vrednosti?
    - Ne, Rc::clone ne vrši duboko kopiranje vrednosti. Umesto toga, Rc::clone povećava broj referenci na podatke koje deli. To znači da samo povećava broj vlasnika resursa, ali ne pravi stvarnu kopiju podataka.
25. Da li `Rc<T>` dozvoljava deljenim vlasnicima da dele i promenljive (Engl. mutable) reference?
    - Ne, Rc<T> ne dozvoljava deljenim vlasnicima (Rc<T>) da dele promenljive referencu. Rc<T> omogućava samo nepromenljive referencije, što znači da više vlasnika može imati jednake nepromenljive referencije na iste podatke, ali ne i promenljive reference. Ako je potrebna promenljiva referenca, trebalo bi koristiti druge pristupe, kao što su RefCell uz Rc<T> ili, ako je threadsafe okruženje, Mutex uz Rc<T> ili Arc<T>.
26. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    enum List {
        Cons(i32, Rc<List>),
        Nil,
    }

    use crate::List::{Cons, Nil};
    use std::rc::Rc;

    fn main() {
        let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
        println!("count after creating a = {}", Rc::strong_count(&a));
        let b = Cons(3, Rc::clone(&a));
        println!("count after creating b = {}", Rc::strong_count(&a));
        {
            let c = Cons(4, Rc::clone(&a));
            println!("count after creating c = {}", Rc::strong_count(&a));
        }
        println!("count after c goes out of scope = {}", Rc::strong_count(&a));
    }
    1
    2
    3
    2
    ```

27. U kom delu memorije se čuvaju ugrađeni nizovi i torke?
    - Ugrađeni nizovi ([T; N]) i torke ((T1, T2, ..., Tn)) obično se smeštaju na stek memoriju. Ovi podaci imaju fiksnu veličinu koja se poznaje u vreme kompilacije, pa su stoga pogodni za smeštanje na stek.
28. U kom delu memorije se čuvaju elementi kolekcije, poput vektora i heš mape?
    - Elementi dinamičkih kolekcija, kao što su vektori (Vec<T>) i heš mape (HashMap<K, V>), smeštaju se na heap memoriju. Ovo je zato što veličina ovih kolekcija može dinamički da raste i smanjuje se tokom izvršavanja programa, a heap omogućava dinamičko alociranje i oslobađanje memorije.
Dakle, dok su ugrađeni nizovi i torke smešteni na steku gde se veličina mora poznati u vreme kompilacije, dinamičke kolekcije koriste heap kako bi se prilagodile promenljivim potrebama tokom izvršavanja programa.

29. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
    let v = Vec::new();
    }
    let v: Vec<i32> = ...
    ```

30. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
    let v = Vec::new();

    v.push(5);
    v.push(6);
    v.push(7);
    v.push(8);
    }
    let mut v...
    ```

31. Koji je rezultat izvršavanja sledećeg koda? Zašto? Ukoliko program proizvodi grešku, izmeni kod tako da se uspešno izvrši.

    ```rust
    fn main() {
        let v = vec![1, 2, 3, 4, 5];
        
        let does_not_exist = &v[100];
    }
    index out of bounds: the len is 5 but the index is 100
    let does_not_exist = v.get(100);
    ```

32. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
    let mut v = vec![1, 2, 3, 4, 5];

    let first = &v[0];

    v.push(6);

    println!("The first element is: {first}");
    }
    Da, jer se pozajmila vrednost u first. A zbog novog alociranja na hipu moze doci do problema prilikom dodavanja novih elemenata.
    ```

33. Da li pravila vlasništva važe i u kontekstu vektora?
    - Da, pravila vlasništva u Rust-u važe i u kontekstu vektora (`Vec<T>`). Vektori se ponašaju kao druge kolekcije u Rust-u i koriste vlasnički model za upravljanje resursima. Evo nekoliko ključnih pravila vlasništva koja se primenjuju na vektore:

        1. **Vlasništvo i Pozajmice (Borrowing):** Vlasnik vektora ima potpunu kontrolu nad resursima koje vektor drži. Pozajmice (nepromenljive i promenljive) se mogu uzeti, ali vlasnik garantuje validnost referenci dok je vlasnik u opsegu.

        2. **Životni vekovi (Lifetimes):** Ako vektor ima reference unutar sebe, životni vekovi igraju ulogu u garantovanju ispravnosti referenci. Rust će zahtevati da referenca u vektoru ne preživi vlasnika vektora.

        3. **Oslobađanje Memorije:** Kada vektor izađe iz opsega, Rust automatski oslobađa memoriju koju je vektor zauzimao. Ovo je deo Rust-ove bezbednosne garancije i eliminacije grešaka u vezi s oslobađanjem resursa.

        4. **Promenljivost (Mutability):** Vlasnik vektora može promeniti vrednosti unutar vektora. Ako se vektor deli između više vlasnika, onda je svaki vlasnik u mogućnosti promeniti vrednosti unutar vektora, pod uslovom da su te promene bezbedne u kontekstu pozajmica i životnih vekova.

        Pravila vlasništva u Rust-u pomažu u očuvanju bezbednosti, sprečavanju trkaža podataka, eliminaciji dangling referenci i održavanju jasnog vlasničkog modela. Vektorske kolekcije u Rust-u koriste ova pravila kako bi obezbedile bezbedno upravljanje memorijom i resursima.
34. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
    let mut v = vec![100, 32, 57];
    for i in &v {
        i += 50;
    }
    }
     for i in &mut v {
        *i += 50;
    }
    ```

35. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    n main() {
    let mut v = vec![100, 32, 57];
    for i in &mut v {
        *i += 50;
        v.push(55)
    }
    }
    Proizvodi jer imamo dva mut pozajmljivanja a sme samo jedno.
    ```

36. Da li je naredni isečak koda ispravan?

    ```rust
    fn main() {
    enum SpreadsheetCell {
        Int(i32),
        Float(f64),
        Text(String),
    }

    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12),
    ];
    }
    Jeste
    ```

37. U kom trenutku se elementi vektora oslobađaju iz memorije?
    - Elementi vektora se oslobađaju iz memorije kada vlasnički vektor izlazi iz opsega. Ovo automatsko oslobađanje memorije deo je Rust-ovog sistema upravljanja vlasništvom i ne zahteva ručno upravljanje dealokacijom resursa. Kada vlasnički vektor (instanca Vec<T>) prestane da bude vidljiv u kodu (na primer, kada izlazi iz opsega funkcije ili bloka), Rust automatski poziva drop metodu koja je odgovorna za oslobađanje resursa. Ova metoda takođe rekurzivno oslobađa resurse za svaki element u vektoru.
38. Koja je razlika između stringa tipa `String` i stringa tipa `str` (ili `&str`)?
    - String i &str su dva različita tipa u Rust-u, a razlike se odnose na vlasništvo i životni vek.

    String predstavlja vlasnički string u heap memoriji. To znači da String ima vlasništvo nad svojim podacima, može se dinamički menjati i automatski se oslobađa kada vlasnik izađe iz opsega.

    &str (ili "referenca na string") predstavlja nepromenljivu referencu na deo stringa. Nema vlasništvo nad podacima, već samo pokazuje na deo stringa. &str često koristimo kao referencu na vrednosti tipa str koje su vlasništvo neke druge strukture (npr. String ili literali).
39. Izmeni sledeći isečak koda koristeći `to_string` metodu nad string literalom:

    ```rust
    fn main() {
        let s = String::from("initial contents");
    }
    let s = "initial contents".to_string();
    ```

40. Da li `push_str` uzima vlasništvo nad parametrom? Proveriti na sledećem primeru koda:

    ```rust
    fn main() {
        let mut s1 = String::from("foo");
        let s2 = "bar";
        s1.push_str(s2);
        println!("s2 is {s2}");
    }
    Ne uzima vlasnistvo.
    Ova metoda se koristi za dodavanje (append) vrednosti tipa &str na postojeći String. Kada se koristi push_str, vlasništvo nad &str ostaje nepromenjeno.
    ```

41. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
        let s1 = String::from("Hello, ");
        let s2 = String::from("world!");
        let s3 = s1 + s2;
    }
    let s3 = s1 + &s2;
    ```

42. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
        let s1 = String::from("Hello, ");
        let s2 = String::from("world!");
        let s3 = s1 + &s2;
        println!("{s1}, {s2}")
    }
    Proizvodi je.
    Operacija konketanacije (+) za stringove u Rust-u prenosi vlasništvo prvog stringa (s1) i onemogućava ga korišćenje nakon toga. Međutim, koristi se pozajmica (&s2) za drugi string koji omogućava efikasno dodavanje vrednosti na kraj prvog stringa.
    ```

43. Koji je rezultat izvršavanja sledećeg koda?

    ```rust
    fn main() {
        let s1 = String::from("tic");
        let s2 = String::from("tac");
        let s3 = String::from("toe");

        let s = format!("{s1}-{s2}-{s3}");
        println!("{s1}, {s2}, {s3}: {s}")
    }
    tic, tac, toe: tic-tac-toe
    ```

44. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
        let s1 = String::from("hello");
        let h = s1[0];
    }
    Da, ovaj kod proizvodi grešku. Rust ne dozvoljava direktno indeksiranje ([]) kod String tipa, jer String može sadržavati više bajtova po karakteru zbog podrške Unicode-a.
    ```

45. Koji je rezultat izvršavanja sledećeg koda?

    ```rust
    #![allow(unused)]
    fn main() {
        let hello = "Здравo";
        let s = &hello[0..4];
        println!("{s}")
    }
    Зд - za svaki karakter se odvaja po 2 bajta
    ```

46. Da li sledeći kod proizvodi grešku?

    ```rust
    #![allow(unused)]
    fn main() {
        let hello = "Здравo";
        let s = &hello[0..1];
        println!("{s}")
    }
    Da. jer slovo Z predstavlja 2 bajta a ne 1.
    ```

47. Koji su ispisi sledeća dva isečka koda?

    ```rust
    // Snippet 1
    #![allow(unused)]
    fn main() {
        for c in "Зд".chars() {
            println!("{c}");
        }
    }
    // Snippet 2
    #![allow(unused)]
    fn main() {
        for b in "Зд".bytes() {
            println!("{b}");
        }
    }
    za prvi slova Z i D
    a za drugi bajtovi za ta slova
    ```

48. Koja je uloga `copied` i `unwrap_or` u sledećem kodu?

    ```rust
    fn main() {
        use std::collections::HashMap;

        let mut scores = HashMap::new();

        scores.insert(String::from("Blue"), 10);
        scores.insert(String::from("Yellow"), 50);

        let team_name = String::from("Blue");
        let score = scores.get(&team_name).copied().unwrap_or(0);
    }  
    U ovom kodu, copied i unwrap_or se koriste u kontekstu rada sa Option vrednostima koje se mogu pojaviti prilikom korišćenja metode get nad HashMap-om.

    copied metoda:

    copied je metoda koja se primenjuje na Option<&T>. Ako je Option neki Some(&T), copied će vratiti Some(T), gde je T kopirajući (implementira Copy). Ako je Option None, copied će ostati None.
    U ovom kontekstu, ako scores.get(&team_name) vrati Some(&value), copied će rezultovati Some(value).
    unwrap_or metoda:

    unwrap_or se primenjuje na Option<T> i uzima drugu vrednost (T) kao argument. Ako je Option Some(value), unwrap_or će vratiti taj value. Ako je Option None, unwrap_or će vratiti predati argument.
    U ovom kontekstu, ako copied rezultat nije None, unwrap_or(0) će vratiti kopiranu vrednost. Ako je copied rezultat None, unwrap_or(0) će vratiti 0.
    ```

49. Iteriraj kroz ključeve i vrednosti sledeće heš mape:

    ```rust
    fn main() {
        use std::collections::HashMap;

        let mut scores = HashMap::new();

        scores.insert(String::from("Blue"), 10);
        scores.insert(String::from("Yellow"), 50);

        // TODO: Add code here
        for (key, value) in &scores{
        println!("{key} {value}");
    }
    }
    
    ```

50. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
        use std::collections::HashMap;

        let mut scores = HashMap::new();

        let blue = String::from("Blue");
        let ten = 10;
        let yellow = String::from("Yellow");
        let fifty = 50;

        scores.insert(blue, ten);
        scores.insert(yellow, fifty);

        println!("{blue}, {ten}; {yellow}, {fifty}")
    }
    Da. Proizvodi je.
    Kada se vrednosti dodele HashMap, vlasništvo se prenosi. To znači da nakon dodele vrednosti scores.insert(blue, ten);, promenljive blue i ten više neće biti validne, jer su njihova vlasništva prenesena u HashMap. Pokušaj korišćenja tih promenljivih nakon toga će prouzrokovati grešku.
    ```

51. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn main() {
        use std::collections::HashMap;

        let mut scores = HashMap::new();

        scores.insert(String::from("Blue"), 10);
        scores.insert(String::from("Blue"), 25);

        println!("{:?}", scores);
    }
    {"Blue": 25}
    ```

52. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn main() {
        use std::collections::HashMap;

        let mut scores = HashMap::new();
        scores.insert(String::from("Blue"), 10);

        scores.entry(String::from("Yellow")).or_insert(50);
        scores.entry(String::from("Blue")).or_insert(50);

        println!("{:?}", scores);
    }
    {"Blue": 10, "Yellow": 50}
    ```

53. U kojoj situaciji se poziva `or_insert` metoda nad `Entry` enumeracijom?
    - Ako ključ postoji, or_insert ažurira vrednost; ako ne postoji, or_insert unosi novu vrednost. 
54. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn main() {
        use std::collections::HashMap;

        let text = "hello world wonderful world";

        let mut map = HashMap::new();

        for word in text.split_whitespace() {
            let count = map.entry(word).or_insert(0);
            *count += 1;
        }

        println!("{:?}", map);
    }
    {"hello": 1, "world": 2, "wonderful": 1}
    ```
