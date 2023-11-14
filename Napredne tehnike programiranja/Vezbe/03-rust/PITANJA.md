# V3 - Programski jezik Rust

## Vlasništvo i pozajmljivanje

1. Šta predstavlja vlasništvo u programskom jeziku Rust?
    -Vlasništvo u programskom jeziku Rust odnosi se na način na koji se upravlja resursima, poput memorije, tokom izvršavanja programa. Rust koristi sistem vlasništva kako bi obezbedio bezbednost memorije, izbegao greške kao što su dangling pointers i null pointer dereferencing, i omogućio efikasno upravljanje resursima.
2. Koja su tri pravila vlasništva?
    -Svaka vrednost ima tačno jednog vlasnika.
    Kada vlasnik izađe iz opsega, resursi koje vlasnik poseduje će biti automatski oslobođeni (dealoocirani).
    Ne može postojati više od jednog promenljivog mutabilnog referenca (mutable reference) ka istom resursu u isto vreme.
3. Koji je opseg važenja varijable?
    -Opseg važenja varijable (scope) u Rustu određuje deo programa u kojem je varijabla vidljiva i može se koristiti. Na primer, varijable koje su definisane unutar funkcije imaju opseg unutar te funkcije. Kada funkcija završi izvršavanje, varijable koje su definisane unutar nje izlaze iz opsega.
4. Da li je string literal (`str`) podrazumevano promenljiv ili nepromenjiv?
    -String literal (str) je nepromenjiv (immutable) u Rustu. String literal je fiksna niska karaktera koja je često ugrađena u izvorni kod programa. Na primer, "Hello, World!" je string literal.
5. Da li su varijable tipa `String` promenljive ili nepromenjive?
    -Varijable tipa String su promenljive (mutable) u Rustu. String je dinamički alokiran string koji može rasti ili se smanjivati tokom izvršavanja programa. Može se menjati, dodavati nove karaktere ili skraćivati, što znači da varijable koje sadrže tip String mogu biti promenljive.
6. U kom trenutku se navedeni String briše iz memorije?

    ```rust
    {
        let s = String::from("hello"); // s is valid from this point forward

        // do stuff with s
    } brise se ovde     
    ```

7. Za šta služi ugrađena funkcija `drop` u Rust-u?
    -Ugrađena funkcija drop u Rust-u koristi se za oslobađanje resursa koje poseduje vlasnik, kada vlasnički objekat izlazi iz opsega. To je deo sistema vlasništva u Rustu i omogućava programeru da definiše posebno ponašanje prilikom oslobađanja resursa, na primer, zatvaranje fajla ili oslobađanje memorije.
8. Koja je interna organizacija `String` objekta? Šta se čuva na steku, a šta se čuva na hipu?
    -Interna organizacija String objekta u Rustu je sledeća:
        Na steku se čuva metadata, kao što su dužina stringa, kapacitet i druge informacije koje su fiksne.
        Na hipu (heap) se dinamički alokira prostor za sadržaj stringa, gde se smeštaju karakteri.
9. Koja je razlika između plitkog kopiranja (Eng. shallow-copy) i dubokog kopiranja (Eng. deep-copy)?
    -Plitko kopiranje (shallow copy) kopira samo referencu na resurs, ne i sam resurs. Duboko kopiranje (deep copy) kopira resurs, zajedno sa svim podresursima koji se nalaze u njemu. Razlika je u tome što plitko kopiranje deli isti resurs između originalnog i kopiranog objekta, dok duboko kopiranje stvara potpuno nezavisne kopije resursa.
10. Pri dodeli `let s2 = s1`, da li programski jezik Rust obavlja plitko kopiranje, duboko kopiranje ili nešto treće?
    -Pri dodeli let s2 = s1 u Rustu se vrši koncept premeštanja (move). Premeštanje znači da vlasništvo nad resursima prelazi sa jedne promenljive na drugu, i originalna promenljiva (s1 u ovom slučaju) gubi vlasništvo. Ovo se često koristi za izbegavanje grešaka vezanih za višestruko oslobođenje resursa.
11. U kontekstu vlasništva, šta predstavlja pojam premeštanja varijabli?
    -Premeštanje varijabli u kontekstu vlasništva u Rustu znači prenos vlasništva nad resursima sa jedne promenljive na drugu. To se često dešava kada se vrši dodela vrednosti drugoj promenljivoj, gde originalna promenljiva više nije validna vlasnica resursa. Premeštanje pomaže u održavanju bezbednosti memorije i sprečavanju problema višestrukog vlasništva nad istim resursima.
12. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn main() {
        let s1 = String::from("hello");
        let s2 = s1;

        println!("{}, world!", s1);
      } bacice error, jer je s2 preuzeo resurs s1
    ```

13. Koja je uloga `Copy` osobine (Eng. trait)?
    -Copy osobina u Rustu je osobina koja označava tipove vrednosti koji se kopiraju prilikom dodele vrednosti. Tipovi koji implementiraju Copy se automatski kopiraju umesto da premeštaju vlasništvo, što znači da originalna i kopirana vrednost mogu mirno koegzistirati bez brige o vlasništvu.
14. Koji tipovi mogu da implementiraju `Copy` osobinu? Upotpuni odgovor sa primerom.
    -Samo tipovi koji zadovoljavaju određene uslove mogu implementirati Copy osobinu. To su obično jednostavni tipovi vrednosti koji se lako kopiraju bit po bit. Na primer, svežnjevi (tuples) i osnovni numerički tipovi poput i32 i f64 mogu implementirati Copy.
        #[derive(Copy, Clone)]
        struct Point {
            x: i32,
            y: i32,
        }

        // Implementacija `Copy` za Point strukturu
        impl Copy for Point {}

        // Funkcija koja koristi `Copy` tip
        fn main() {
            let p1 = Point { x: 1, y: 2 };
            let p2 = p1;  // Kopiranje umesto premeštanja
            println!("p1: {:?}, p2: {:?}", p1, p2);
        }
15. Da li referenca ima vlasništvo nad objektom koji pokazuje?
    -Ne, referenca nema vlasništvo nad objektom koji pokazuje. Reference služe kao "pozajmljeni" pokazivači na vrednosti, ali same po sebi ne poseduju vlasništvo.
16. Šta predstavlja pojam pozajmljivanja?
    -Pojam pozajmljivanja u Rustu odnosi se na privremeno preuzimanje referenca na vrednost, obično u svrhu čitanja ili modifikacije, ali bez trajnog preuzimanja vlasništva.
17. Da li su reference podrazumevano nepromenjive?
    -Da, reference su podrazumevano nepromenjive (immutable) u Rustu. Ova osobina doprinosi bezbednosti memorije, jer sprečava nepredvidljive promene vrednosti putem referenci.
18. Da li referenca može da bude promenljiva?
    -Da, referenca može da bude promenljiva (mutable) ako je deklarisana sa &mut.
19. Koliko promenljivih referenci na isti objekat može da postoji u istom opsegu? Zašto?
    -U jednom opsegu može postojati ili jedna promenljiva referenca ili proizvoljan broj nepromenljivih referenci na isti objekat. Ovo pravilo je deo sistema pozajmljivanja i vlasništva u Rustu, dizajnirano kako bi se izbegli problemi višestrukog mutiranja.
20. Pod kojim uslovima se dešava trka do podataka?
    -Trka do podataka (data race) javlja se kada dva ili više niti pristupaju deljenim podacima, gde barem jedna od njih vrši pisanje, bez odgovarajuće sinhronizacije. Ovo može dovesti do nedefinisanog ponašanja i grešaka u programu. Rust garantuje bezbednost od trka do podataka zahvaljujući svojim sistemima vlasništva i pozajmljivanja.
21. Da li mogu da postoje promenljiva i nepromenjiva referenca u istom opsegu u isto vreme?
    -Ne, ne mogu postojati istovremeno promenljiva i nepromenljiva referenca na isti objekat u istom opsegu u Rustu. Ovo pravilo doprinosi bezbednosti i jasnoći vlasništva, sprečavajući potencijalne greške koje mogu nastati usled kombinacije čitanja i pisanja u isto vreme.
22. Da li je naredni isečak koda ispravan?

    ```rust
    fn main() {
      let mut s = String::from("hello");

      let r1 = &s;
      let r2 = &s;
      println!("{} and {}", r1, r2);

      let r3 = &mut s;
      println!("{}", r3);
    } jeste
    ```

23. Koji je opseg (vreme života) reference?
    -Opseg (vreme života) reference u Rustu se odnosi na period tokom kojeg je referenca validna i može se bezbedno koristiti. Rust koristi sistem vlasništva i pozajmljivanja kako bi garantovao bezbednost tokom upotrebe referenci. Opseg reference je obično ograničen na opseg (scope) u kojem je referenca definisana. Kada referenca izađe iz opsega, postaje nevažeća, a Rust automatski oslobađa resurse koje je referenca koristila.
24. Šta predstavlja viseći pokazivač (referenca) (Eng. dangling pointer)?
    -Viseći pokazivač (referenca) (dangling pointer) je pokazivač koji pokazuje na memorijsku lokaciju koja više nije validna, jer je resurs koji je pokazivao oslobođen. U Rustu, zahvaljujući bezbednosti vlasništva, dangling pointeri su teško postižući jer kompilator sprečava situacije u kojima bi se resursi mogli osloboditi pre nego što se referenca izađe iz opsega. Ova bezbednosna svojstva doprinose smanjenju rizika od visećih pokazivača u Rust programima.
25. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
      let reference_to_nothing = dangle();
    }

    fn dangle() -> String {
        let s = String::from("hello");

        s
    }
    ```

26. Da li je sledeća tvrdnja tačna? *U svakom trenutku možemo imati ili jednu promenjivu ili proizvoljan broj nepromenjivih referenci*
    -Tvrdnja nije tačna. U Rustu, pravilo je da možete imati ili jednu promenljivu referencu ili proizvoljan broj nepromenjivih referenci na isti objekat u okviru jednog opsega (scope). Ovo pravilo sprečava potencijalne konflikte između pisanja i čitanja vrednosti iz istog objekta.
27. Šta predstavlja isečak (Eng. slice)?
    -Isečak (slice) u Rustu predstavlja referencu na deo kolekcije, kao što su niz ili vektor. Isečak se koristi za rad sa podnizovima bez potrebe za kopiranjem celokupne kolekcije. Isečci se koriste za prenose ili pozajmljivanje dela kolekcije, a često se koriste u kombinaciji sa referencama.
28. Na koji način kreiramo string isečak?
    -String isečak se kreira pomoću sintakse range-a (opsega). Na primer, možete kreirati isečak određenog opsega indeksa u stringu.
        let originalni_string = String::from("Hello, World!");

        // Kreiranje isečka od 7. do 12. karaktera (indeksi počinju od 0)
        let isečak = &originalni_string[7..12];

29. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn first_word(s: &String) -> &str {
      let bytes = s.as_bytes();

      for (i, &item) in bytes.iter().enumerate() {
          if item == b' ' {
              return &s[0..i];
          }
      }

      &s[..]
    }

    fn main() {
        let mut s = String::from("hello world");

        let word = first_word(&s);

        s.clear();

        println!("the first word is: {}", word);
    } // vratice error jer se ocisti string s i word vise ne pokazuje ni na sta
    ```

30. Da li string literali predstavljaju string isečke? Ukoliko jesu, da li su promenljivi ili nepromenjivi?
    -Da, string literali u Rustu predstavljaju string isečke. String literali su nepromenjivi (immutable) isečci, što znači da ne možete ih menjati. Oni su tipa &str, što je referenca na nepromenjivi niz karaktera. Ovi isečci obično imaju statički vektor bajtova u memoriji i ne mogu se menjati nakon što su definisani.
    let literalni_string: &str = "Hello, World!";

31. Odredi tip isečka u sledećem kodu:

    ```rust
    let a = [1, 2, 3, 4, 5];

    let slice = &a[1..3];
    ``` // &[i32]

32. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn first_word(s: &str) -> &str {
      let bytes = s.as_bytes();

      for (i, &item) in bytes.iter().enumerate() {
          if item == b' ' {
              return &s[0..i];
          }
      }

      &s[..]
    }

    fn main() {
        let my_string = String::from("hello world");

        let word = first_word(&my_string[0..6]);
        let word = first_word(&my_string[..]);

        let word = first_word(&my_string);

        let my_string_literal = "hello world";

        let word = first_word(&my_string_literal[0..6]);
        let word = first_word(&my_string_literal[..]);

        let word = first_word(my_string_literal);
    }
    /*
    let word = first_word(&my_string[0..6]);
    Rezultat: "hello" (isečak od prvog do šestog karaktera u stringu).

    let word = first_word(&my_string[..]);
    Rezultat: "hello world" (ceo string jer nema razmaka).

    let word = first_word(&my_string);
    Rezultat: "hello" (isečak do prvog razmaka).

    let word = first_word(&my_string_literal[0..6]);
    Rezultat: "hello" (isečak od prvog do šestog karaktera u string literalu).

    let word = first_word(&my_string_literal[..]);
    Rezultat: "hello world" (ceo string literal jer nema razmaka).

    let word = first_word(my_string_literal);
    Rezultat: "hello" (isečak do prvog razmaka u string literalu).

    Ova funkcija first_word radi na referencama na &str i pravilno vraća isečke prvih reči iz zadatih stringova ili string literala.    
    */
    ```
    

33. Ispravi greške u sledećem kodu:

    ```rust
    fn main() {
    let s = String::from("hello");  // s comes into scope

    takes_ownership(&s);             
    println!("{}", s);

    let x = 5;                      

    makes_copy(x);   
    
    println!("{}", x)
  } 

  fn takes_ownership(some_string: &String) {
      println!("{}", some_string);
  } 
  fn makes_copy(some_integer: i32) {
      println!("{}", some_integer);
  }
  // nema greske
    ```

34. Odredi rezultat izvršavanja sledećeg koda:

    ```rust
    fn main() {
      let s1 = gives_ownership(); 

      let s2 = String::from("hello");

      let s3 = takes_and_gives_back(s2);
    }

    fn gives_ownership() -> String {
        let some_string = String::from("yours");

        some_string 
    }

    fn takes_and_gives_back(a_string: String) -> String {
        a_string
    } // s1 dobija vrednost yours
        // s2 dobija hello
        // s3 dobija hello i s2 gubi vlasnistvo
    ```