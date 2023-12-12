# V7 - Programski jezik Rust

## Generički tipovi, osobine, životni vek

1. Umesto dve funkcije `largest_i32` i `largest_char`, napiši jednu funkciju koja podržava generičke tipove i pruža istu funkcionalnost u `main` metodi.

    ```rust
        fn largest_i32(list: &[i32]) -> &i32 {
        let mut largest = &list[0];

        for item in list {
            if item > largest {
                largest = item;
            }
        }

        largest
    }

    fn largest_char(list: &[char]) -> &char {
        let mut largest = &list[0];

        for item in list {
            if item > largest {
                largest = item;
            }
        }

        largest
    }

    fn main() {
        let number_list = vec![34, 50, 25, 100, 65];

        let result = largest_i32(&number_list);
        println!("The largest number is {}", result);
        assert_eq!(*result, 100);

        let char_list = vec!['y', 'm', 'a', 'q'];

        let result = largest_char(&char_list);
        println!("The largest char is {}", result);
        assert_eq!(*result, 'y');
    }
    ```
    Solution
    ```rust
                
    fn largest<T: std::cmp::PartialOrd + Copy>(list: &[T]) -> T{
        let mut largest = list[0];

        for &item in list{
            if item > largest{
                largest = item;
            }
        }
        largest
    }
    fn main() {
        let number_list = vec![34, 50, 25, 100, 65];

        let result = largest(&number_list);
        println!("The largest number is {}", result);
        assert_eq!(result, 100);

        let char_list = vec!['y', 'm', 'a', 'q'];

        let result = largest(&char_list);
        println!("The largest char is {}", result);
        assert_eq!(result, 'y');
    }
    ```

2. Pronađi i ispravi grešku u sledećem isečku koda.
    ```rust
    struct Point<T> {
        x: T,
        y: T,
    }

    fn main() {
        let wont_work = Point { x: 5, y: 4.0 };
    }
    ```
    Solution
    ```rust
    struct Point<T, Y> {
        x: T,
        y: Y,
    }

    fn main() {
        let wont_work = Point { x: 5, y: 4.0 };
    }
    ```

3. Da li je dozvoljeno koristiti generičke tipove unutar enumeracija? Ukoliko da, navedi primer.
     Jeste
    enum Option\<T>{
        Some\<T>,
        None
    }
4. Šta je rezultat izvršavanja sldećeg isečka koda na `stdout`?

    ```rust
    struct Point<X1, Y1> {
        x: X1,
        y: Y1,
    }

    impl<X1, Y1> Point<X1, Y1> {
        fn mixup<X2, Y2>(self, other: Point<X2, Y2>) -> Point<X1, Y2> {
            Point {
                x: self.x,
                y: other.y,
            }
        }
    }

    fn main() {
        let p1 = Point { x: 5, y: 10.4 };
        let p2 = Point { x: "Hello", y: 'c' };

        let p3 = p1.mixup(p2);

        println!("p3.x = {}, p3.y = {}", p3.x, p3.y);
    }
    ```
    - Rezultat je da ce p3 kao x vrednost imati vrednost x-a tacke p1, a kao y ce imati vrednost tacke u y p2

5. Da li korištenje generičkih tipova utiče na vreme izvršavanja programa (Engl. Runtime overhead)? Razjasniti.
    - Ne. Употреба генеричког кода не доводи до деградације перформанси. Раст користи технику мономорфизације (Monomorphization) код које ће компајлер инстанцирати конкретан кôд за сваки тип посебно.
6. Koji koncept iz Rust-a je sličan intefejsima iz drugih jezika? Koje su razlike između njih?
    - Traits. Traits u Rust-u omogućavaju definisanje metoda koje tip treba implementirati, čime se omogućava deljenje funkcionalnosti između različitih tipova. 

    Sličnosti:

        Definisanje zajedničkog interfejsa: Kao i interfejsi u drugim jezicima, traits omogućavaju definisanje zajedničkog seta funkcionalnosti koje tipovi mogu implementirati.

        Polimorfizam: Traits u Rust-u omogućavaju polimorfizam, gde se metode mogu pozivati na vrednosti različitih tipova, ali samo ako ti tipovi implementiraju odgovarajući trait.

        Generičko programiranje: Traits se često koriste u kombinaciji sa generičkim tipovima kako bi se omogućila apstrakcija i ponovno korišćenje koda.

    Razlike:

        Odsustvo nasleđivanja: Za razliku od interfejsa u nekim drugim jezicima, traiti u Rust-u ne podržavaju nasleđivanje. Svaki tip mora eksplicitno implementirati trait da bi dobio njegovu funkcionalnost.

        Eksplicitna implementacija: Implementacija traita za određeni tip se vrši eksplicitno. Ovo je deo Rust-ovog sistema bezbednosti jer omogućava preciznu kontrolu nad implementacijom traita i sprečava konflikte imena.

        Associated types: Rust-ovi traiti podržavaju asocijativne tipove (associated types), što je koncept koji omogućava traitu da definiše tipove podataka koji se koriste unutar traita, a da ih implementirajući tipovi mogu specificirati. Ovo može biti korisno za dinamičko upravljanje tipovima u okviru traita.

        Prednosti ownership modela: Traits u Rust-u su često dizajnirani s obzirom na Rust-ov ownership model. To znači da se traits mogu koristiti da se obezbedi sigurnost i efikasnost u radu s vlasništvom i pozajmicama.

7. Da li je moguće implementirati `Display` osobinu (Engl. Trait) za `Vec<T>`? Zašto?
    -  Da, moguće je implementirati Display trait za Vec<T> u Rust-u. Display trait se koristi za formatiranje vrednosti kada se koristi makro format!, println! ili druge funkcije koje zahtevaju formatiranje teksta.
8. Da li je moguće pozivati uobičajenu (Engl. Default) implementaciju iz naknadne (Engl. Overriding) implementacije iste metode?
    - U Rust-u, nije moguće direktno pozivati uobičajenu (Default) implementaciju iz naknadne (overriding) implementacije iste metode. U Rust-u, trenutno ne postoji direktna podrška za super pozive iz implementacija trait-a. Ovo je svesna odluka u dizajnu kako bi se izbegle određene zamke i povećala jasnoća koda.
9. Šta je rezultat izvršavanja sldećeg isečka koda na `stdout`?

    ```rust
    pub trait Summary {
        fn summarize_author(&self) -> String;

        fn summarize(&self) -> String {
            format!("(Read more from {}...)", self.summarize_author())
        }
    }


    pub struct Tweet {
        pub username: String,
        pub content: String,
        pub reply: bool,
        pub retweet: bool,
    }

    impl Summary for Tweet {
        fn summarize_author(&self) -> String {
            format!("@{}", self.username)
        }
    }


    pub struct NewsArticle {
        pub headline: String,
        pub location: String,
        pub author: String,
        pub content: String,
    }

    impl Summary for NewsArticle {
        fn summarize_author(&self) -> String {
            format!("@{}", self.author)
        }

        fn summarize(&self) -> String {
            format!("{}, by {} ({})", self.headline, self.author, self.location)
        }
    }


    fn main() {
        let article = NewsArticle {
            headline: String::from("Penguins win the Stanley Cup Championship!"),
            location: String::from("Pittsburgh, PA, USA"),
            author: String::from("Iceburgh"),
            content: String::from(
                "The Pittsburgh Penguins once again are the best \
                hockey team in the NHL.",
            ),
        };

        println!("New article available! {}", article.summarize());
        
        
        let tweet = Tweet {
            username: String::from("horse_ebooks"),
            content: String::from(
                "of course, as you probably already know, people",
            ),
            reply: false,
            retweet: false,
        };

        println!("1 new tweet: {}", tweet.summarize());
        }
     ```
    - New article available! Penguins win the Stanley Cup Championship!, by Iceburgh (Pittsburgh, PA, USA)
    1 new tweet: (Read more from @horse_ebooks...) 
    
10. Pojednostavi sledeći kod koristeći sintaksu za ograničenja kroz osobine  (Engl. Trait bounds).

    ```rust
    pub fn notify(item1: &impl Summary, item2: &impl Summary)

    // solution
    pub fn notify<T: Summary>(item1: &T, item2: &T){}

    ```

11. Pojednostavi sledeći kod koristeći sintaksu za ograničenja kroz osobine  (Engl. Trait bounds).
    ```rust
    pub fn notify(item: &(impl Summary + Display)) {}
    // solution
    pub fn notify1<T: Summary + Display>(item: &T) {}

    ```

12. Napiši ekvivalentni kod koristeći `where` klauzulu.

    ```rust
    fn some_function<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 {}
    // solution
    fn some_function<T, U>(t: &T, u: &U) -> i32 
    where T: Display + Clone,
            U: Clone + Debug
        {}
    ```

13. Da li sledeći kod proizvodi grešku?

    ```rust
        pub trait Summary {
        fn summarize_author(&self) -> String;

        fn summarize(&self) -> String {
            format!("(Read more from {}...)", self.summarize_author())
        }
    }


    pub struct Tweet {
        pub username: String,
        pub content: String,
        pub reply: bool,
        pub retweet: bool,
    }

    impl Summary for Tweet {
        fn summarize_author(&self) -> String {
            format!("@{}", self.username)
        }
    }


    pub struct NewsArticle {
        pub headline: String,
        pub location: String,
        pub author: String,
        pub content: String,
    }

    impl Summary for NewsArticle {
        fn summarize_author(&self) -> String {
            format!("@{}", self.author)
        }

        fn summarize(&self) -> String {
            format!("{}, by {} ({})", self.headline, self.author, self.location)
        }
    }


    fn main() {
        let article = NewsArticle {
            headline: String::from("Penguins win the Stanley Cup Championship!"),
            location: String::from("Pittsburgh, PA, USA"),
            author: String::from("Iceburgh"),
            content: String::from(
                "The Pittsburgh Penguins once again are the best \
                hockey team in the NHL.",
            ),
        };

        println!("New article available! {}", article.summarize());
        
        
        let tweet = Tweet {
            username: String::from("horse_ebooks"),
            content: String::from(
                "of course, as you probably already know, people",
            ),
            reply: false,
            retweet: false,
        };

        println!("1 new tweet: {}", tweet.summarize());
    }
    
    
    fn returns_summarizable(switch: bool) -> impl Summary {
        if switch {
            NewsArticle {
                headline: String::from(
                    "Penguins win the Stanley Cup Championship!",
                ),
                location: String::from("Pittsburgh, PA, USA"),
                author: String::from("Iceburgh"),
                content: String::from(
                    "The Pittsburgh Penguins once again are the best \
                    hockey team in the NHL.",
                ),
            }
        } else {
            Tweet {
                username: String::from("horse_ebooks"),
                content: String::from(
                    "of course, as you probably already know, people",
                ),
                reply: false,
                retweet: false,
            }
        }
    }
    ```
    - Da. impl Trait синтакса за повратне вредности је могућа само ако функција враћа један тип који имплементира дату особину.

14. Šta predstavlja `blanket` implementacija?
    - Blanket implementacija u Rust-u se odnosi na situaciju kada se trait implementira za sve tipove koji zadovoljavaju određeni kriterijum, umesto za svaki tip pojedinačno. To omogućava implementaciju trait-a za sve tipove koji ispunjavaju određene uslove, čime se postiže veća generičnost i olakšava rad s različitim tipovima.
    ```rust
        trait MyClone {
    fn my_clone(&self) -> Self;
    }

    // Blanket implementacija za sve tipove koji implementiraju Copy trait
    impl<T: Copy> MyClone for T {
        fn my_clone(&self) -> Self {
            *self
        }
    }
    ```
15. Šta je životni vek reference (Engl. Reference Lifetime)?
    - To je opseg u kome je referenca validna.
16. Da li sledeći kod proizvodi grešku? Ukoliko da, ispravi je.

    ```rust
    fn main() {
        let r: i32;
        println!("r: {}", r);
    }
    // solution
        let r: i32 = 0;
    ```

17. Da li sledeći kod prozvodi grešku? Zašto? Pomoć: *viseća referenca* (Engl. dangling pointer).

    ```rust
    fn main() {
        let r;

        {
            let x = 5;
            r = &x;
        }

        println!("r: {}", r);
    }
    
    ```
    - Proizvodi zato sto pozajmljena vrednost ne zivi van opsega u kom je pozajmljena. U ovom slucaju x je ispustena dok je idalje pozajmljena.

18. Kako funkcioniše `borrow checker` u Rust-u?
    - Borrow checker je deo sistema pozajmica i vlasništva u Rust-u koji se koristi tokom kompilacije kako bi se garantovala sigurnost upravljanja pozajmicama i vlasništvom, a time i prevencija određenih vrsta grešaka, poput dangling references i race conditions.

    Evo kako borrow checker funkcioniše u Rust-u:

        Pozajmice i vlasništvo: Rust koristi koncepte pozajmica i vlasništva kako bi pratila ko ima pristup podacima i na koji način. Ako želimo da pozajmimo vrednost, možemo to učiniti kao pozajmicu koja može biti ili promenljiva (&mut T) ili nepromenljiva (&T). Rust prati ove pozajmice tokom životnog veka programa.

        Životni vekovi (lifetimes): Rust koristi životne vekove kako bi pratio koliko dugo važe određene pozajmice. Životni vek se označava apostrofom (') i često se koristi kao generički parameter u funkcijama ili strukturama koje rukuju referencama.

        Pravila pozajmica: Borrow checker primenjuje određena pravila kako bi se obezbedilo bezbedno korišćenje pozajmica. Neki od ključnih principa uključuju:

            Ne može postojati više od jedne promenljive koja poseduje promenljivu pozajmicu (&mut T) unutar istog opsega.
            Nepromenljive pozajmice (&T) mogu postojati u više instanci, ali ne mogu postojati zajedno sa promenljivom pozajmicom unutar istog opsega.
            Životni vekovi pozajmica moraju biti kompatibilni sa životnim vekovima vlasnika podataka.
        Reference i ownership: Rust traži od programera da jasno definiše vlasništvo i životne vekove, što vodi ka jasnijem kodu i prevenciji određenih grešaka. Ownership model, zajedno sa borrow checker-om, eliminiše potrebu za garbage collector-om i omogućava sigurno paralelno izvršavanje.

    Kroz ove mehanizme, borrow checker omogućava Rust-u da garantuje da nema dangling references, data races ili drugih grešaka koje proizilaze iz nepravilnog rukovanja vlasništvom i pozajmicama. Ovo doprinosi Rust-ovoj reputaciji kao jeziku koji pruža visok nivo sigurnosti uz relativno nizak overhead.
    ```rust
        {
    let r;                // ---------+-- 'a
                          //          |
    {                     //          |
        let x = 5;        // -+-- 'b  |
        r = &x;           //  |       |
    }                     // -+       |
                          //          |
    println!("r: {}", r); //          |
    }                         // ---------+
    ```
    - Програм је одбачен јер r референцира вредност чији животни век ('b) је краћи од животног века варијабле r ('a). Уколико би се ово дозволило, r би у једном делу референцирала невалидну вредност.
19. Pronađi i ispravi greške u sledećem isečku koda.

    ```rust
    fn main() {
        let string1 = String::from("abcd");
        let string2 = "xyz";

        let result = longest(string1.as_str(), string2);
        println!("The longest string is {}", result);
    }

    fn longest(x: &str, y: &str) -> &str {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
    // solution
    fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
    ```

20. Da li je sledeći kod validan? Zašto?

    ```rust
    fn main() {
        let string1 = String::from("long string is long");

        {
            let string2 = String::from("xyz");
            let result = longest(string1.as_str(), string2.as_str());
            println!("The longest string is {}", result);
        }
    }

    fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
    Jeste.  јер референца која се враћа може бити x или y у зависности од дужине стринга.
    Овим кажемо компајлеру да за неки генерички животни век 'a, функција прима две референце чији животни век вредности обухвата 'a и враћа референцу која мора бити валидна бар колико и животни век 'a тј. животни век повратне референце мора да обухвати 'a. Уколико такав животни век постоји код се прихвата.
    ```

21. Da li se sledeći kod uspešno kompajlira? Zašto?

    ```rust
    fn main() {
        let string1 = String::from("long string is long");
        let result;
        {
            let string2 = String::from("xyz");
            result = longest(string1.as_str(), string2.as_str());
        }
        println!("The longest string is {}", result);
    }

    fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
    Ne. Jer string2 ne zivi dovoljno dugo. Result se koristi van opsega u kom je deklarisana vrednost od string2.
    ```

22. Popravi greške u sledećem isečku koda.

    ```rust
    fn main() {
        let string1 = String::from("abcd");
        let string2 = "xyz";

        let result = longest(string1.as_str(), string2);
        println!("The longest string is {}", result);
    }

    fn longest<'a>(x: &str, y: &str) -> &'a str {
        let result = String::from("really long string");
        result.as_str()
    }
    // solution
    fn longest(x: &str, y: &str) -> String {
        let result = String::from("really long string");
        result
    }
    ```

23. Popravi greške u sledećem isečku koda.

    ```rust
    struct ImportantExcerpt {
        part: &str,
    }

    fn main() {
        let novel = String::from("Call me Ishmael. Some years ago...");
        let first_sentence = novel.split('.').next().expect("Could not find a '.'");
        let i = ImportantExcerpt {
            part: first_sentence,
        };
    }
    // solution
    struct ImportantExcerpt<'a> {
    part: &'a str,
    }

    ```

24. Šta su ulazni i izlazni životni vekovi (Engl. Input and Output Lifetimes)?
    - Ulazni životni vekovi (input lifetimes): Ovo se odnosi na životne vekove koji se primenjuju na referencu kao ulaznom parametru funkcije. Oni pomažu kompilatoru da razume kako će životni vekovi referenci unutar funkcije biti povezani sa životnim vekovima referenci koje funkcija prima.

    - Izlazni životni vekovi (output lifetimes): Ovo se odnosi na životne vekove referenci koje funkcija vraća kao rezultat. Izlazni životni vekovi pomažu kompilatoru da razume kako će životni vekovi vraćenih referenci biti povezani sa životnim vekom drugih referenci u programu.
25. Šta su pravila za *eliziju životnog veka* (Engl. Lifetime Elision)?
    - Pravilo 1: Kompajler kreira zivotni vek za svaku referencu u parametrima funkcije.
    - Pravilo 2 (Input lifetimes): Ako postoji tačno jedan ulazni životni vek, životni vek tog ulaza postaje životni vek svih izlaznih referenci.
    - Pravilo 3 (Multiple input lifetimes): Ako postoje više ulaznih životnih vekova, ali jedan od njih je &self ili &mut self, životni vek &self ili &mut self postaje životni vek svih izlaznih referenci.
26. Da li su nam potrebne eksplicitne anotacije životnog veka u sledećem primeru? Zašto?

    ```rust
    fn first_word(s: &str) -> &str {
    ```
    - U datom primeru, ne trebaju nam eksplicitne anotacije životnog veka jer Rust koristi pravilo elizije životnog veka koje automatski određuje životni vek referenci u određenim situacijama.

    - U funkciji first_word, &str je referenca na string slice, a životni vek te reference će biti automatski određen prema pravilima elizije životnog veka. U ovom slučaju, Rust će automatski zaključiti da životni vek reference koju vraća funkcija first_word mora biti vezan za životni vek ulazne reference s. To se radi automatski, pa programeru nije potrebno eksplicitno navođenje životnog veka.

27. Popravi greške u sledećem isečku koda.

    ```rust
    struct ImportantExcerpt<'a> {
        part: &'a str,
    }

    impl ImportantExcerpt {
        fn level(&self) -> i32 {
            3
        }
    }

    impl ImportantExcerpt {
        fn announce_and_return_part(&self, announcement: &str) -> &str {
            println!("Attention please: {}", announcement);
            self.part
        }
    }

    fn main() {
        let novel = String::from("Call me Ishmael. Some years ago...");
        let first_sentence = novel.split('.').next().expect("Could not find a '.'");
        let i = ImportantExcerpt {
            part: first_sentence,
        };
    }
    // solution
    impl<'a> ImportantExcerpt<'a> {
        fn level(&self) -> i32 {
            3
        }
    }

    impl<'a> ImportantExcerpt<'a> {
        fn announce_and_return_part(&self, announcement: &str) -> &str {
            println!("Attention please: {}", announcement);
            self.part
        }
    }
    ```

28. Napiči ekvivalentan kod koji koristi eksplicitan životni vek.

    ```rust
    let s: &str = "I have a static lifetime.";
    // solution
    let s: &'static str = "I have a static lifetime.";

    ```

29. Koliko je dugačak životni vek string literal-a?
    - Životni vek string literala u Rust-u ima statički životni vek i vezan je za ceo tok programa. String literali su smešteni direktno u izvršni fajl i imaju životni vek koji traje tokom celog izvršenja programa.
30. Koja ja razlika između korišćenja asociranih tipova i generičkih tipova pri implementaciji osobina?
    - Generički tipovi: Kada koristite generičke tipove u Rust-u, implementacija osobina (trait-a) može biti generička, što znači da se trait može primeniti na različite tipove.
    ```rust
    trait MyTrait<T> {
        fn do_something(&self, value: T);
    }

    struct MyStruct;

    impl MyTrait<i32> for MyStruct {
        fn do_something(&self, value: i32) {
            // implementacija za i32
        }
    }

    impl MyTrait<String> for MyStruct {
        fn do_something(&self, value: String) {
            // implementacija za String
        }
    }

    ```
    - Asocirani tipovi: Asocirani tipovi su povezani sa trait-om, ali se mogu koristiti samo kada je trait implementiran za konkretan tip. Oni omogućavaju definisanje tipova koji su vezani za implementaciju određenog trait-a.
    ```rust
    trait MyTrait {
        type MyType;
        fn do_something(&self, value: Self::MyType);
    }

    struct MyStruct;

    impl MyTrait for MyStruct {
        type MyType = i32;

        fn do_something(&self, value: i32) {
            // implementacija za i32
        }
    }

    ```
31. Da li sledeći kod izaziva `panic`?

    ```rust
    use std::ops::Add;

    #[derive(Debug, Copy, Clone, PartialEq)]
    struct Point {
        x: i32,
        y: i32,
    }

    impl Add for Point {
        type Output = Point;

        fn add(self, other: Point) -> Point {
            Point {
                x: self.x + other.x,
                y: self.y + other.y,
            }
        }
    }

    fn main() {
        assert_eq!(
            Point { x: 1, y: 0 } + Point { x: 2, y: 3 },
            Point { x: 3, y: 3 }
        );
    }
    ```
    - Ne izaziva panic.

32. Zašto sledeći primer koristi `Add<Meters>` a ne samo `Add` kao prethodni?

    ```rust
    use std::ops::Add;

    struct Millimeters(u32);
    struct Meters(u32);

    impl Add<Meters> for Millimeters {
        type Output = Millimeters;

        fn add(self, other: Meters) -> Millimeters {
            Millimeters(self.0 + (other.0 * 1000))
        }
    }
    ```
    - Korišćenje generičkog Add bi značilo da implementacija obuhvata sve moguće tipove koji implementiraju Add, što može biti nepotrebno opšte i neprecizno u ovom kontekstu. Dakle, eksplicitnim navođenjem Add<Meters>, jasno definišete koji tipovi su dopušteni u okviru ove implementacije trait-a za vašu strukturu Millimeters.
33. Šta je rezultat ivršavanja sledećeg isečka koda?

    ```rust
    trait Pilot {
        fn fly(&self);
    }

    trait Wizard {
        fn fly(&self);
    }

    struct Human;

    impl Pilot for Human {
        fn fly(&self) {
            println!("This is your captain speaking.");
        }
    }

    impl Wizard for Human {
        fn fly(&self) {
            println!("Up!");
        }
    }

    impl Human {
        fn fly(&self) {
            println!("*waving arms furiously*");
        }
    }

    fn main() {
        let person = Human;
        person.fly();
    }
    ```
    - *waving arms furiously*

34. Ponovo napiši `main` funckiju iz prethodnog primera tako da se pozovu sve 3 implementacije `fly` metode.
    ```rust
    fn main() {
        let person = Human;
        Pilot::fly(&person);
        Wizard::fly(&person);  
        person.fly();
    }
    ```
35. Šta je rezultat izvršavanja sledećeg isečka koda?

    ```rust
    trait Animal {
        fn baby_name() -> String;
    }

    struct Dog;

    impl Dog {
        fn baby_name() -> String {
            String::from("Spot")
        }
    }

    impl Animal for Dog {
        fn baby_name() -> String {
            String::from("puppy")
        }
    }

    fn main() {
        println!("A baby dog is called a {}", Dog::baby_name());
    }
    ```
    - A baby dog is called a Spot
36. Ponovo napiši `main` funkciju iz prethodnog primera tako da poziva obe `baby_name` metode.
    ```rust
    
    fn main() {
        println!("A baby dog is called a {}", Dog::baby_name());
        println!("A baby dog is called a {}", <Dog as Animal>::baby_name());
    }
    ```
37. Sledeći kod se ne kompajlira. Implementiraj odgovarajuću osobinu na `Point` tipu.
    ```rust
    use std::fmt;

    trait OutlinePrint: fmt::Display {
        fn outline_print(&self) {
            let output = self.to_string();
            let len = output.len();
            println!("{}", "*".repeat(len + 4));
            println!("*{}*", " ".repeat(len + 2));
            println!("* {} *", output);
            println!("*{}*", " ".repeat(len + 2));
            println!("{}", "*".repeat(len + 4));
        }
    }

    struct Point {
        x: i32,
        y: i32,
    }
    
    impl OutlinePrint for Point {}
    ```
    solution
    ```rust
    use std::fmt::{Display, Formatter, Result};

    trait OutlinePrint: Display {
        fn outline_print(&self) {
            let output = self.to_string();
            let len = output.len();
            println!("{}", "*".repeat(len + 4));
            println!("*{}*", " ".repeat(len + 2));
            println!("* {} *", output);
            println!("*{}*", " ".repeat(len + 2));
            println!("{}", "*".repeat(len + 4));
        }
    }

    struct Point {
        x: i32,
        y: i32,
    }

    impl Display for Point {
        fn fmt(&self, f: &mut Formatter<'_>) -> Result {
            write!(f, "({}, {})", self.x, self.y)
        }
    }

    impl OutlinePrint for Point {}

    fn main() {
        let point = Point { x: 10, y: 20 };
        point.outline_print();
    }

    ```
38. Implementiraj `Display` osobinu na `Vector<T>` tipu.
    ```rust
    use std::fmt::{Display, Formatter, Result};

    struct Vector<T> {
        x: T,
        y: T,
        z: T,
    }

    impl<T: Display> Display for Vector<T> {
        fn fmt(&self, f: &mut Formatter<'_>) -> Result {
            write!(f, "({}, {}, {})", self.x, self.y, self.z)
        }
    }


    ```
39. Šta sledeći kod prikazuje na `stdout`?

    ```rust
    fn main() {
        type Kilometers = i32;
        let x: i32 = 5;
        let y: Kilometers = 5;
        println!("x + y = {}", x + y);
    }
    ```
    - x + y = 10
40. Šta je *never type*?
    - Never type u Rust-u označava tip koji se nikada ne može vratiti ili završiti normalno. U Rust-u, ovaj tip se često označava sa ! (uskladišteno sa uzvičnikom). On se koristi kada se funkcija nikada ne završava normalno, na primer, kada dolazi do beskonačne petlje, panic! makroa ili kada funkcija baca izuzetak.
    ```rust
    fn never_ending_function() -> ! {
        loop {
            // beskonačna petlja
        }
    }

    ```
41. Šta su divergirajuće funkcije (Engl. Divering functions)?
    - Divergirajuće funkcije su funkcije koje nikada ne završavaju normalno, odnosno ne vraćaju vrednost tipa (). Ove funkcije se obično označavaju kao funkcije koje imaju never type (!) kao povratni tip. To znači da ne dolazi do povratne vrednosti, već može doći do beskonačne petlje, panic-a ili nečeg sličnog.

    Primer divergirajuće funkcije u Rust-u može biti funkcija koja koristi loop za beskonačnu petlju:
    ```rust
    fn never_ending_function() -> ! {
        loop {
            // beskonačna petlja
        }
    }

    ```
42. Koji je tip `guess` varijable u sledećem isečku koda?

    ```rust
            let guess: u32 = match guess.trim().parse() {
                Ok(num) => num,
                Err(_) => continue,
            };
    ```
    - Tip je u32

43. Šta je tip `loop` izraza u sledećem isečku koda?

    ```rust
        print!("forever ");

        loop {
            print!("and ever ");
        }
    ```
    - (), poznat i kao unit type. U Rust-u, izrazi i blokovi u okviru loop konstrukcije imaju vrednost () jer loop predstavlja beskonačnu petlju koja se izvršava zauvek. 
44. Da li se sledeći isečak koda uspešno kompajlira? Zašto?

    ```rust
    fn main() {
        let s1: str = "Hello there!";
        let s2: str = "How's it going?";
    }
    ```
    - Ne. U Rust-u, str nije tip podataka koji se koristi za deklaraciju string literala kao što to radite u drugim jezicima. Umesto toga, za statičke string literale se obično koristi tip &str, a za dinamičke stringove (heap-allocated) se koristi tip String.
    Ovo bi radilo:
    ```rust
    fn main() {
        let s1: &str = "Hello there!";
        let s2: &str = "How's it going?";
    }

    ```
45. Da li su osobine tipovi dinamičke veličine (Engl. Dynamically Sized)?
    - Da, osobine (traits) su tipovi dinamičke veličine u Rust-u. To znači da se veličina vrednosti koja implementira određenu osobinu ne zna u vreme kompilacije, već se određuje u toku izvršavanja
46. Koja osobina je korisna u toku rada sa tipovima dinamičke veličine (DST - Dynamically Sized Type)?
    - Osobina koja je posebno korisna u radu sa tipovima dinamičke veličine je Sized. Sized je ugrađena Rust osobina koja je automatski implementirana za sve tipove čija je veličina poznata u vreme kompilacije (statički veličinski tipovi). Kada imate tip koji je dinamički veličine, to znači da nije Sized, i morate koristiti specifične mehanizme, kao što su pokazivači, referenca ili druge strukture podataka, kako biste radili s takvim tipovima.
47. Da li generičke funkcije uobičajeno podržavaju rad sa tipovima dinamičke veličine?
    - Generičke funkcije u Rust-u, podrazumevano, rade sa tipovima koji su poznati u vreme kompilacije, tj. sa statički veličinskim tipovima. Međutim, ako želite podržati generičke funkcije koje rade sa tipovima dinamičke veličine, možete koristiti grananje preko osobine Sized. Na primer:
    ```rust
    fn example<T: ?Sized>(value: &T) {
    // Funkcija koja radi sa tipovima dinamičke veličine
    // T: ?Sized omogućava generičnost i za Sized i za !Sized tipove
    }

    ```
    Ovde T: ?Sized označava da T može biti i statički veličinski tip i dinamički veličinski tip. To omogućava generičke funkcije da rade sa različitim tipovima, uključujući one čija veličina nije poznata u vreme kompilacije.