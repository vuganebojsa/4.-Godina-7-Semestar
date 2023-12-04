# V6 - Programski jezik Rust

## Paketi, moduli, obrada grešaka, testiranje

1. Iz kojih elemenata se sastoji Rust-ov sistem za module?
    - Moduli: Omogućavaju organizaciju koda tako što grupišu povezane funkcionalnosti.
    Podmoduli: Unutar modula mogu postojati podmoduli koji omogućavaju još dublje organizovanje koda.
    Strukture (Structs) i Enumeracije (Enums): Mogu se koristiti unutar modula.
    Funkcije i Metode: Takođe, mogu biti deo modula.
2. Šta je sanduk (Engl. Crate)?
    - Сандук представља најмању количину кода коју Раст компајлер обрађује у једном тренутку.
    Сандук може бити у форми бинарног сандука и библиотечког сандука.
    
3. Šta je binarni sanduk (Engl. Binary Crate)?
    - Бинарни сандук представља програме који могу да се компајлирају и покрену. Ови сандуци имају функцију main која представља улазну тачку.
4. Šta je bibliotečki sanduk (Engl. Library Crate)?
    - Библиотечки сандуци представљају функционалност намењену за дељење са другим пројектима.
    Корен сандука представља почетни фајл од кога Раст компајлер креће, односно представља коренски модул.
5. Šta je koren (Engl. Root) sanduka?
    - Корен сандука представља почетни фајл од кога Раст компајлер креће, односно представља коренски модул.
6. Šta je paket (Engl. Package)?
    - Пакет представља скуп логички повезаних сандука којима се управља на јединствен начин.
7. Koliko binarnih ili bibliotečkih sanduka može da se nalazi u jednom paketu?
    - Proizvoljno mnogo binarnih, ali najvise jedan bibliotecki sanduk.
8. Šta je uobičajen koren za binarni sanduk? A za bibliotečki sanduk?
    - src/main.rs za binarni, a za bibliotecki je src/lib.rs
9. Gde se još binarni sanduci mogu nalaziti?
    - Ако пакет има више бинарних сандука, коренски фајлови се смештају у фолдер src/bin.
10. Koje konvencije bismo trebali da pratimo dok definišemo module (Engl. Modules) u sanducima?
    - Korišćenje CamelCase za Nazive Modula, Pisanje Kratkih i Deskriptivnih Naziva Modula,
    Organizacija Modula U Stablu Direktorijuma, Korišćenje Modifikatora Privatnosti (pub),
    Razdvajanje Binarnih i Bibliotečkih Sanduka, Organizovanje Zajedničkog Koda u Biblioteke
11. Da li su moduli uobičajeno privatni?
    - Moduli su podrazumevano privatni, a da bi se drugi kod mogao referencirati na njih, potrebno je eksplicitno navesti pub (public).
12. Kako formiramo putanju do stavke (metoda ili funkcija) u stablu modula (Engl. Module Tree)?
    - Koristi se dvostruki dvotačak (::) za formiranje putanje do stavke u stablu modula.
13. Da li uobičajeno roditeljski modul (Engl. Parent Module) ima pristup sadržaju unutrašnjeg modula?
    - Da, roditeljski modul može pristupiti sadržaju unutrašnjeg modula ukoliko je deo modifikatora privatnosti (public).   Inače, unutrašnji modul je privatno dostupan.
14. Pozovi funkciju `add_to_waitlist` uz pomoć apsolutne i relativne putanje na naznačenim mestima:

    ```rust
    mod front_of_house {
        mod hosting {
            fn add_to_waitlist() {}
        }
    }

    pub fn eat_at_restaurant() {
        // TODO: Apsolutna putanja
        crate::cront_of_house::hosting::add_to_waitlist();
        // TODO: Relativna putanja
        front_of_house::hosting::add_to_waitlist();
    }
    ```

15. Uzimajući u obzir prethodno pitanje, zašto može `eat_at_restaurant` da pristupi privatnom modulu `front_of_house`?
    - Zato sto su oba dela koda(funkcija i modul) deo istog spoljnog, globalnog modula.
16. Za šta se koristi ključna reč `super`?
    - Kada relativnu putanju kreiramo sa pocetkom u roditeljskom modulu
17. Ispravi grešku u sledećem kodu:

    ```rust
    mod back_of_house {
        pub struct Breakfast {
            pub toast: String,
            // dodato pub
            pub seasonal_fruit: String,
        }

        impl Breakfast {
            pub fn summer(toast: &str) -> Breakfast {
                Breakfast {
                    toast: String::from(toast),
                    seasonal_fruit: String::from("peaches"),
                }
            }
        }
    }

    pub fn eat_at_restaurant() {
        // Order a breakfast in the summer with Rye toast
        let mut meal = back_of_house::Breakfast::summer("Rye");
        // Change our mind about what bread we'd like
        meal.toast = String::from("Wheat");
        println!("I'd like {} toast please", meal.toast);

        meal.seasonal_fruit = String::from("blueberries");
    }

    fn main() {
        eat_at_restaurant();
    }
    ```

18. Zašto funkcija `summer` mora biti javna (Engl. Public)?
    - Funkcija summer mora biti javna (pub) zato što se koristi izvan modula back_of_house - tačnije, koristi se u funkciji eat_at_restaurant 
19. Ukoliko je enum javan, da li su i njegove varijacije javne? A strukture (Engl. Structs)?
    - Ako je enum javan, sve njegove varijante postaju javne. To znači da možete pristupiti varijantama enuma izvan modula u kojem je enum definisan, pod uslovom da je sam enum obeležen sa pub.
    Za strukture, situacija je drugačija. Ako je sama struktura obeležena sa pub, to ne znači automatski da su svi njeni polja javni. Svako polje strukture ima svoj sopstveni modifikator privatnosti.
20. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    mod front_of_house {
        pub mod hosting {
            pub fn add_to_waitlist() {}
        }
    }

    use crate::front_of_house::hosting;

    mod customer {
        pub fn eat_at_restaurant() {
            hosting::add_to_waitlist();
        }
    }
    Proizvodi zbog putanje hosting::add_to_wl, treba da se doda super ispred. Jer smo dodali fju u modul pa se mora pozvati super da uzme modul iznad.
    ```

21. Navedi dva načina da se ispravi greška u sledećem isečku koda:

    ```rust
    mod front_of_house {
        pub mod hosting {
            pub fn add_to_waitlist() {}
        }
    }

    use crate::front_of_house::hosting;

    mod customer {
        pub fn eat_at_restaurant() {
            hosting::add_to_waitlist();
        }
    }

    fn main() {
        customer::eat_at_restaurant();
    }
    //prvi nacin:
        super::hosting:;add_to_wl
    //drugi nacin
    u modulu customer uraditi use crate...
    ```

22. Koji je proces ponovnog export-ovanja (Engl. Re-Export) imena?
    - Када уведемо име у опсег са use он је приватан за приступ споља.
    Уколико желимо да буде јаван споља можемо користити pub use.
23. Kako dodajemo i koristimo spoljne pakete (Engl. External Package) kao zavisnosti (Engl. Dependency) u našem Rust projektu?
    - dodamo ispod [dependencies] u Cargo.toml ime_paketa = verzija
        dodamo ga u fajl koristeci use ime::...
24. Šta je naziv sanduka standardne biblioteke (Engl. Standard Library)?
    - Standardna biblioteka Rusta poznata je kao std (standard).
    Rust standardna biblioteka pruža osnovne funkcionalnosti kao što su rad sa stringovima, upravljanje niti, kolekcije, i mnoge druge stvari.
    Sanduk std je uključen u svaki Rust program automatski, tako da nije potrebno eksplicitno navoditi ga kao zavisnost u Cargo.toml.
25. Prepiši sledeći isečak koda da bude koncizniji:

    ```rust
    use std::cmp::Ordering;
    use std::io;
    // use std::{io, cmp::Ordering};

    ```

26. Prepiši sledeći isečak koda da bude koncizniji:

    ```rust
    use std::io;
    use std::io::Write;
    // use std::io::{self, Write};
    ```
27. Glob operator
    -Ако желимо да уведемо све елементе неког модула можемо писати:
        use std::collections::*;

27. Koji tipovi grešaka su podržani u Rust programskom jeziku i kako se ponašaju?
    - грешке код којих је могућ опоравак (recoverable)
        Грешке које очекивано могу да се десе у току рада и које можемо да обрадимо и наставимо извршавање без нарушавања конзитентности стања програма.
    грешке код којих опоравак није могућ (unrecoverable)
        Увек су симптом багова у програму, нпр. читање ван опсега низа.
        Једини логичан поступак је прекид рада програма.
28. Kako mozemo da izazovemo `panic` u Rust-u?
    - Sa makrom panic!
29. Šta je odmotavanje (Engl. unwinding) i kako se sprečava?
    - Odmotavanje (Unwinding) u Rustu odnosi se na proces koji se dešava kada program doživi paniku (panic) ili drugi izuzetan događaj. Odmotavanje je mehanizam koji omogućava programu da se "odmotava" unazad kroz stek okvire (stack frames) kako bi se pravilno zatvorile resursi i izvršile neophodne akcije pre nego što se program zatvori.

    Kada dođe do panike, Rust automatski izvršava odmotavanje kako bi se osiguralo da se resursi pravilno oslobode pre nego što program završi. Ovo uključuje zatvaranje otvorenih fajlova, oslobađanje memorije i druge čiste-up operacije.

    Odmotavanje se može sprečiti u Rustu korišćenjem makroa panic!. Makro panic! se koristi da generiše paniku, ali ona ne omogućava automatsko odmotavanje. Umesto toga, program se odmah prekida.
30. Da li se u sledećem isečku koda događa `panic`? Ukoliko da, kako možemo pokazati celokupni povratni trag (Engl. Backtrace)?

    ```rust
    fn main() {
        let v = vec![1, 2, 3];

        v[99];
    }
    ```
    - Da, u ovom isečku koda dolazi do panike. Razlog je pokušaj pristupa elementu van granica vektora (v[99]), što će uzrokovati panicu u Rustu. 
    a biste dobili celokupni povratni trag (backtrace) u Rustu, možete koristiti biblioteku backtrace. Dodajte ovu zavisnost u Cargo.toml: backtrace = "0.3.63"
    use backtrace::Backtrace;

        fn main() {
            // Postavite okruženje da biste prikazali informacije o panici
            std::env::set_var("RUST_BACKTRACE", "1");

            // Postavite funkciju za obradu panika
            std::panic::set_hook(Box::new(|panic_info| {
                let backtrace = Backtrace::new();
                eprintln!("PANIC: {:?}", panic_info);
                eprintln!("BACKTRACE: {:?}", backtrace);
            }));

            // Simulacija panike
            let v = vec![1, 2, 3];
            v[99];
        }


31. Ukoliko postoji, pokušaj otvoriti `hello.txt`, u suprotnom iskoristi `panic`. Reši problem koristeći `match`.
    - 
        use std::fs::File;

        fn main() {
            let greeting_file_result = File::open("hello.txt");

            let greeting_file = match greeting_file_result {
                Ok(file) => file,
                Err(error) => panic!("Problem opening the file: {:?}", error),
            };
        }
32. Reši prethodni problem pomoću leksičkog zatvaranja (Engl. Lexical Closure).
    let file = File::open("hello.txt")
        .map(|file| file)
            .unwrap_or_else(|error| panic!("sadas));
33. Isti problem reši koristeći `unwrap`.
     use std::fs::File;

        fn main() {
            let greeting_file = File::open("hello.txt").unwrap();
        }
34. Isti problem reši koristeći `expect`.
    fn main() {
            let greeting_file_result = File::open("hello.txt").expect("problem opening the file");

        }
35. Šta je bolje koristiti: `unwrap` ili `expect`?
    zbor između unwrap i expect zavisi od specifičnih potreba i preferencija u različitim situacijama. Oba metoda se koriste za rukovanje Result-ima u Rustu i izazivaju panicu ako rezultat sadrži grešku (Err).

unwrap:
unwrap je kraći i jednostavniji, ali ne pruža korisniku mogućnost pružanja dodatne poruke.
expect Koristi se kada je dodavanje informativne poruke korisno za razumevanje razloga panike.
Bolje je expect zbog te poruke
36. Sledeći isečak koda prepiši u kraći i ekvivalentan kod koristeći `?`. Nije dozvoljeno korišćenje `fs::read_to_string`.

    ```rust
    #![allow(unused)]
    fn main() {
        use std::fs::File;
        use std::io::{self, Read};

        fn read_username_from_file() -> Result<String, io::Error> {
            let username_file_result = File::open("hello.txt");

            let mut username_file = match username_file_result {
                Ok(file) => file,
                Err(e) => return Err(e),
            };

            let mut username = String::new();

            match username_file.read_to_string(&mut username) {
                Ok(_) => Ok(username),
                Err(e) => Err(e),
            }
        }
    }
    /*
        #![allow(unused)]
        fn main() {
            use std::fs::File;
            use std::io::{self, Read};

            fn read_username_from_file() -> Result<String, io::Error> {
                let mut username_file_result = File::open("hello.txt")?;

                let mut username = String::new();

                username_file_result.read_to_string(&mut username)?;
                Ok(username)
            }
        }       
    */
    ```

37. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    use std::fs::File;

    fn main() {
        let greeting_file = File::open("hello.txt")?;
    }
    // jer operator ? može se koristiti samo unutar funkcija koje imaju povratni tip Result ili Option, a ne direktno unutar funkcije main.
    ```

38. Šta može biti povratni tip main funkcije?
    - Povratni tip main funkcije u Rustu može biti bilo koji tip koji implementira std::process::Termination. Ovo uključuje tipove kao što su (), i32, Result<(), E> i druge tipove koji predstavljaju završetak programa.
39. Podseti se igre pogađanja brojeva [na sledećem linku](https://doc.rust-lang.org/book/ch02-00-guessing-game-tutorial.html). Izmeni kod da takođe proverava da li je korisnikov unos u rasponu [1, 100]. Ovu proveru uradi tako što napišeš svoju `Guess` strukturu sa konstruktorom koji izaziva `panic` ukoliko vrednost nije u očekivanom rasponu.
