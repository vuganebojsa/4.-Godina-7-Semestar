# V1 - Programski jezik Rust

## Početak

1. Koji su nazivi paketa koda u Rust programskom jeziku?
    -    Nazivaju se karakteristikama(features)
2. Gde se postavlja izvorni kod u sanduku (Engl. Crate)?
    - Izvorni kod se postavlja u "sanduk" (engl. "Crate"), što je osnovna jedinica za organizaciju i distribuciju   Rust koda. Sanduk je direktorijum koji sadrži Rust kod, biblioteke i manifest fajl.
3. Gde Cargo postavlja izvršive fajlove?
    -Cargo postavlja izvršive fajlove u "target" direktorijum unutar vašeg projekta, u poddirektorijumima koji zavise od ciljne platforme (npr. "debug" ili "release" za različite konfiguracije).
4. Koja je svrha `Cargo.toml` i `Cargo.lock` fajlova?
    -Cargo.toml je manifest fajl za Rust projekte i sadrži konfiguraciju projekta, uključujući zavisnosti i karakteristike. Cargo.lock je fajl koji automatski generiše Cargo i koristi se za "zaključavanje" verzija zavisnosti, osiguravajući doslednost okoline za razvoj i izgradnju projekta.

## Igra pogađanja brojeva

1. Šta je uvodni skup (Engl. prelude set)?
    -Uvodni skup (Prelude Set): U Rust programskom jeziku, "prelude set" je grupa osnovnih modula i funkcija koje su automatski dostupne svuda u Rust kodu. Ovo uključuje često korišćene module i funkcije, poput std::io, std::vec::Vec, std::string::String, itd.
2. Da li su varijable podrazumevano promenljive ili nepromenjive? Da li isto važi i za reference?
    -U Rustu, varijable su podrazumevano nepromenljive (engl. "immutable"). Da biste napravili promenljivu, koristite ključnu reč mut. Reference prate isto pravilo; podrazumevano su nepromenljive. Da biste omogućili promenljive reference, takođe koristite ključnu reč mut.
3. Šta predstavlja asocirana funkcija? Navedi par primera.
    -Asocirane funkcije su funkcije koje su povezane sa tipom (strukturom, enumeracijom) umesto sa instancom tog tipa. Na primer, String::from("hello") je poziv asocirane funkcije from za tip String.
4. Šta je varijacija (variant)?
    -U Rust enumeracijama, varijacije su različite vrednosti koje može uzeti enumeracija. Na primer, u enumeraciji enum Color { Red, Green, Blue }, Red, Green i Blue su varijacije.
5. Koja dva tipa sanduka (Engl. crate) postoje? Navedi glavnu razliku izmedju njih.
    -U Rustu postoje dva tipa sanduka - biblioteka (engl. "library crate") i izvršna (engl. "binary crate"). Glavna razlika je da biblioteka služi za deljenje funkcionalnosti i može se uključiti u druge projekte, dok je izvršna sanduk aplikacija koja se izvršava kao samostalna aplikacija.
6. Koji je unapred podešeni registar za open source sanduke?
    -Unapred podešeni registar za open source sanduke u Rust ekosistemu je "crates.io". To je centralni registar gde programeri mogu deliti Rust biblioteke i pakete koda.
7. Kako `Cargo.lock` fajl omogućava ponovljivost izradnje?
    -Cargo.lock fajl čuva informacije o tačnim verzijama zavisnosti korišćenih u projektu. Ovo osigurava ponovljivost izgradnje tako da druge osobe ili sistemi mogu tačno reprodukovati istu okolinu sa istim verzijama zavisnosti.
8. Kog tipa je `std::cmp::Ordering` i koje vrednosti može uzeti?
    - std::cmp::Ordering je enumeracija koja predstavlja tri moguća rezultata poređenja - "Manje" (Less), "Veće" (Greater) i "Jednako" (Equal).
9. Od čega se sastoji `match` izraz?
    -match izraz u Rustu sastoji se od "šablona" (engl. "patterns") i odgovarajućih akcija(grane) koje se izvršavaju ako se šabloni podudaraju sa vrednostima.
10. Pri definisanju celog broja, koji je uobičajni tip koji Rust jezik koristi?
    - U Rustu, uobičajeni tip za celobrojne vrednosti je i32 (32-bitni potpisani ceo broj).
11. Da li je senčenje (Engl. Shadowing) promenljivih dozvoljeno u istom opsegu (Engl. scope)?
    -Da, senčenje promenljivih je dozvoljeno u istom opsegu. To znači da možete ponovo definisati promenljivu sa istim imenom u okviru istog opsega i nova vrednost će "zamračiti" prethodnu vrednost.
