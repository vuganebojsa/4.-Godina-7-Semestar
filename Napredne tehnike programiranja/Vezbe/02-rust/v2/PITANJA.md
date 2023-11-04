# V2 - Programski jezik Rust

## Osnovni programski koncepti

1. Da li su varijable podrazumevano promenljive?
- Jesu
2. Popravi greške pri kompajliranju sledećeg koda:

```rust 
fn main() {
    let mut x = 5;
    println!("The value of x is: {x}");
    x = 6;
    println!("The value of x is: {x}");
}
```

3. Koje su glavne razlike između konstanti i nepromenljivih varijabli?
    - konstante se deklarisu pomocu kljucne reci const i moraju imati eksplicitno naveden tip, dok se promenljive deklarisu sa kljucnom reci let i mogu da imaju automatski zakljucen tip
4. Šta predstavlja životni opseg konstante?
    - definise se sa const i moze biti globalni opseg ili opseg fje, ali ne moze se menjati tokom izvrsavanja programa
5. Odredi rezultat izvršavanja sledećeg koda:

```rust
fn main() {
    let x = 5;

    let x = x + 1;

    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {x}");
    }

    println!("The value of x is: {x}");
}
```
    - value in scope is 12
    - out of scope is 6
6. Koja je razlika između senčenja promenljivih (Engl. Shadowing) i promenljivosti?
    - Sencenje omogucava deklaraciju nove promenljive sa istim imenom unutar istog opsega, pri cemu nova promenjiva zasenjuje prethodnu. Promenljivost se odnosi na mogucnost promene vrednosti promenljive nakon inicijalizacije
7. Da li je Rust statički ili dinamički tipiziran jezik?
    - staticki, tipovi se moraju odrediti tokom kompilacije
8. Da li sledeći kod proizvodi grešku? Ukoliko da, ispravi je.

```rust
let guess: u32 = "42".parse().expect("Not a number!");
```

9. Koja je veličina `isize` i `usize` tipova?
    - na 32bitnom racunaru su oba tipa 4 bajta, dok su na 64bitnom oba tipa 8 bajta
10. Da li je `57u8` validna vrednost?
    - nije jer prelazi opseg vrednosti u8 tipa
11. Napredno pitanje: Kako se Rust ponaša u slučaju prelivanja vrednosti broja (Engl. Integer Overflow) [Integer Overflow](https://en.wikipedia.org/wiki/Integer_overflow)?
    - Ponasa se sigurno. Tretirace se kao greska i pgroam ce se obustaviti.
12. Koja je veličina `bool` tipa? Koja je veličina `char` tipa?
    - 1 bajt, a char 4 bajta
13. Koji su primitivni složeni (Engl. compound) tipovi?
    - tuple i nizovi
14. Gde se nizovi alociraju u memoriji?
    - na steku ili hipu u zavisnosti o tome kako su deklarisani ili korisceni
15. Šta su elementi iskaza `let a = [3; 5];`? Šta predstavljaju `3` i `5`?
    - 3 predstavlja vrednost kojom ce biti popunjeni elementi niza, a 5 predstavlja duzinu niza
16. Šta je ulazna tačka za Rust program?
    - fn main()
17. Šta znači kada se za Rust tvrdi da je jezik baziran na izrazima (Engl. Expression-based)?
    - Vecina stvari koje se desavaju u jeziku su izrazi koji vracaju vrednost. Cak i iskazi kao sto su if izrazavaju vrednosti

18. Da li opseg predstavlja izraz? Upotpuni odgovor sa primerom.
    - Opseg se ne smatra izrazom. To je deo koda u kojem se promenljive mogu koristiti
    {
        let mut a = 5;
    }
19. Za šta služi `;`?
    - za zavrsetak izraza u rustu
20. Da li je sledeća definicija validna?

```rust
fn five() -> i32 {
  5
}
- Jeste, vraca 5
```

21. Šta je rezultat izvršavanja sledećeg koda?

```rust
fn main() {
    let x = plus_one(5);

    println!("The value of x is: {x}");
}

fn plus_one(x: i32) -> i32 {
    x + 1;
}
Greska, kad se stavi ; na kraj ne vraca se vrednost
```

22. Šta su linijski komentari u Rust-u?
    - // sve nakon nnjih se ignorise
23. Šta predstavljaju "ruke" (Engl. arms) u Rust-u?
    - odnosi se na razlicite grane iskaza match, gde se svaka grana naziva rukama i odgovara odredjenom obrascu
24. Šta je rezultat izvršavanja sledećeg koda?

```rust
fn main() {
    let number = 3;

    if number {
        println!("number was three");
    }
}
Error, trazi bool ne moze samo broj
```

25. Da li ključna reč `if` prestavlja izraz u Rust-u?
    - Da, predstavlja izraz i moze se koristiti za dodeljivanje vrednosti promenljivoj
26. Šta je rezultat ivršavanja sledećeg koda?

```rust
fn main() {
    let condition = true;

    let number = if condition { 5 } else { "six" };

    println!("The value of number is: {number}");
}
Error, tipovi se moraju podudarati
```

27. Šta je rezultat izvršavanja sledećeg koda?

```rust
fn main() {
    let mut counter = 0;

    let result = loop {
        counter += 1;

        if counter == 10 {
            break counter * 2;
        }
    };

    println!("The result is {result}");
}
Rezultat je 20
```

28. Za svaki `break` iskaz navedi koja je sledeća linija u toku izvršavanja.

```rust
fn main() {
    let mut count = 0;
    'counting_up: loop {
        println!("count = {count}");
        let mut remaining = 10;

        loop {
            println!("remaining = {remaining}");
            if remaining == 9 {
                break;
            }
            if count == 2 {
                break 'counting_up;
            }
            remaining -= 1;
        }

        count += 1;
    }
    println!("End count = {count}");
}
Prvi brejk izlazi iz ugnjezdene petlje, dok drugi izlazi iz spoljne petlje
```
