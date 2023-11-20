# V4 - Programski jezik Rust

## Strukture, enumeracije i podudaranje obrazaca

1. Pojednostavi instanciranje strukture `User` u funkciji `build_user`:

    ```rust
    struct User {
      active: bool,
      username: String,
      email: String,
      sign_in_count: u64,
    }

    fn build_user(email: String, username: String) -> User {
        User {
            active: true,
            username,
            email,
            sign_in_count: 1,
        }
    }
    ```

2. Pojednostavi kreiranje instance `user2` iz instance `user1` upotrebom sintakse za ažuriranje. Da li se `user1` može koristiti nakon instanciranja `user2`? Zašto?

    ```rust
    let user2 = User {
          active: user1.active,
          username: user1.username,
          email: String::from("another@example.com"),
          sign_in_count: user1.sign_in_count,
    };

    let user2 = User {
        email: String::from("another@example.com"),
        ..user1
  };
  Ne moze se koristiti nakon user2 jer se vrednost od usera pozajmi u user2. Da smo mu pozajmili samo active i sign_incount ne bi bilo problema jer implementiraju copy tip.
    ```

3. Da li su `black` i `origin` isti tip?

    ```rust
    struct Color(i32, i32, i32);
    struct Point(i32, i32, i32);

    fn main() {
        let black = Color(0, 0, 0);
        let origin = Point(0, 0, 0);
    }
    Jesu isti tip jer su obe tuple, ali su razlicite strukture.
    ```

4. Da li je naredni isečak koda ispravan?

    ```rust
    struct AlwaysEqual;

    fn main() {
        let subject = AlwaysEqual;
    }
    Jeste ispravan, to je unit struct sto znaci da nema polja.
    Ovo se koristi kad nam je prisutnost tipa bitnija nego sama vrednost te instance tipa.
    ```

5. Kreiraj strukturu `Rectangle` sa dva polja: `height` i `weight`. Nakon toga, kreiraj funkciju koja izračunava površinu pravougaonika na osnovu instance pravougaonika. Ispisati instancu strukture `Rectangle` upotrebom #[derive] atributa.
    - 
    #[derive(Debug)]
    struct Rectangle{
        width: u32,
        height: u32
    }
    impl Rectangle{
        fn area(&self) -> u32{
            self.width * self.height
        }
    }
    fn main(){
        let rect = Rectangle{
            width:30,
            height:30
        };
        println!("{:?}", rect.area());
    }
    
6. Implementiraj gorenavedeni zadatak upotrebom metode umesto asocirane funkcije.
    - fn area(rectangle: &Rectangle) -> u32{
        rectangle.width * rectangle.height
    }
7. Nad kojim sve tipovima se može definisati metoda?
    - Nad strukturama, enumeracijama, osnovne tipove podataka, reference, mutable reference
8. Koja je razlika između `self` i `Self`?
    - self se koristi unutar metode da oznaci instancu nad kojom se ta metoda poziva, to je ref na trenutni objekat ili instancu. Self se koristi kao tip za oznacavanje povratnog tipa metode ili asocij funkcije koja se poziva na tip, a ne na instancu.
9. Da li metoda uzima vlasništvo nad `self`?
    - Podrazumevano uzimaju pozamljene reference nad self, sto znaci da ne preuzimaju vlasnistvo. To se cesto naziva pozajmljivanje &self ili &mut self
10. Kada bi metoda trebala da uzme vlasništvo nad `self`?
    - Kada zelimo da prenesemo vlasnistvo nad resursima koje instanca poseduje. U prevodu kad iskoristimo neku metodu ne zelimo da to sto smo preneli od objekta dalje koristimo.
    fn consume(self) -> ...{
        self.neka_vred
    }
11. Implementiraj asociranu funkciju nad `Rectangle` koja se zove `square` i koja kreira instancu `Rectangle` koja predstavlja kvadrat (dimenzije obe stranice su iste). Primer upotrebe funkcije je: `let sq = Rectangle::square(3)`;
impl Rect{
    fn square(size: u32) -> Self{
        Self{
            width:size,
            height:size
        }
    }
}
12. Da li struktura može da ima više `impl` blokova?
    - Moze
13. Šta predstavljaju enumeracije u Rust-u?
14. Pojednostavi sledeći primer upotrebom samo enumeracije:

    ```rust
    fn main() {
      enum IpAddrKind {
          V4,
          V6,
      }

      struct IpAddr {
          kind: IpAddrKind,
          address: String,
      }

      let home = IpAddr {
          kind: IpAddrKind::V4,
          address: String::from("127.0.0.1"),
      };

      let loopback = IpAddr {
          kind: IpAddrKind::V6,
          address: String::from("::1"),
      };
    }
    ```

15. Da li sledeći kod proizvodi grešku? Ukoliko da, ispravi je.

    ```rust
    fn main() {
      enum IpAddr {
          V4(u8, u8, u8, u8),
          V6(String),
      }

      let home = IpAddr::V4(127, 0, 0, 1);

      let loopback = IpAddr::V6(String::from("::1"));
    }
    ```

16. Da li Rust ima koncept `null` vrednosti?
17. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
      let _absent_number = None;
    }
    ```

18. Koje su prednosti upotrebe `Option<T>` umesto `null`?
19. Šta je rezultat izvršavanja sledećeg koda?

    ```rust
    #[derive(Debug)]
    enum UsState {
        Alabama,
        Alaska,
        // --snip--
    }

    enum Coin {
        Penny,
        Nickel,
        Dime,
        Quarter(UsState),
    }

    fn value_in_cents(coin: Coin) -> u8 {
        match coin {
            Coin::Penny => 1,
            Coin::Nickel => 5,
            Coin::Dime => 10,
            Coin::Quarter(state) => {
                println!("State quarter from {:?}!", state);
                25
            }
        }
    }

    fn main() {
        value_in_cents(Coin::Quarter(UsState::Alaska));
    }
    ```

20. Šta je rezultat izvršavanja sledećeg koda?

    ```rust
    fn main() {
      fn plus_one(x: Option<i32>) -> Option<i32> {
          match x {
              None => None,
              Some(i) => Some(i + 1),
          }
      }

      let five = Some(5);
      let six = plus_one(five);
      let none = plus_one(None);
      
      println!("five: {:#?}, six: {:#?}, none: {:#?}", five, six, none)
    }
    ```

21. Šta je rezultat izvršavanja sledećeg koda?

    ```rust
    fn main() {
      fn plus_one(x: Option<i32>) -> Option<i32> {
          match x {
              Some(i) => Some(i + 1),
          }
      }

      let five = Some(5);
      let six = plus_one(five);
      let none = plus_one(None);
      
      println!("five: {:#?}, six: {:#?}, none: {:#?}", five, six, none)
    }
    ```

22. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
      let dice_roll = 9;
      match dice_roll {
          3 => add_fancy_hat(),
          7 => remove_fancy_hat(),
      }

      fn add_fancy_hat() {}
      fn remove_fancy_hat() {}
    }
    ```

23. Iskoristi `if let` umesto `match` izraza u sledećem primeru:

    ```rust
    fn main() {
      let config_max = Some(3u8);
      match config_max {
          Some(max) => println!("The maximum is configured to be {}", max),
          _ => (),
      }
    }
    ```

24. Koja je razlika `if let` u odnosu na `match`?
25. Iskoristi `if let` umesto `match` izraza u sledećem primeru:

    ```rust
    #[derive(Debug)]
    enum UsState {
        Alabama,
        Alaska,
        // --snip--
    }

    enum Coin {
        Penny,
        Nickel,
        Dime,
        Quarter(UsState),
    }

    fn main() {
        let coin = Coin::Penny;
        let mut count = 0;
        match coin {
            Coin::Quarter(state) => println!("State quarter from {:?}!", state),
            _ => count += 1,
        }
        println!("The count is: {}", count)
    }
    ```
