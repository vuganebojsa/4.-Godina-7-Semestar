# V8 - Programski jezik Rust

## Pametni pointeri (drugi deo), FP, iteratori i zatvorenja

1. Šta predstavlja obrazac interne promenjivosti?
    - RefCell<T>
    - Дизајн образац за измену података чак и када постоје дељене референце.
    Ово је забрањено правилима позајмљивања.
    Интерно користи несигуран кôд (unsafe) чиме се ставља до знања компајлеру да се провера обавља од стране RefCell<T> типа.
    Провера се сели из времена компајлирања у време извршавања (run-time)
2. Koja je razlika između `Box<T>` i `RefCell<T>`?
    - Код Box<T> правила позајмљивања се проверавају у време компајлирања (статички). Ако прекршимо правила кôд се неће компајлирати.
    Код RefCell<T> правила позајмљивања се проверавају у време извршавања. Ако прекршимо правила програм ће прекинути са извршавањем (panic).
3. U kojoj situaciji je potrebno da se pravila pozajmljivanja proveravaju u vreme izvršavanja programa umesto u vreme kompajliranja?
    - RefCell<T> користимо у ситуацијама када знамо да је наш програм валидан али Раст компајлер то није у стању да верификује статички.
4. Izmeni sledeći kod upotrebom `RefCell<T>` tako da se testovi uspešno izvrše:

    ```rust
    pub trait Messenger {
    fn send(&self, msg: &str);
    }

    pub struct LimitTracker<'a, T: Messenger> {
        messenger: &'a T,
        value: usize,
        max: usize,
    }

    impl<'a, T> LimitTracker<'a, T>
    where
        T: Messenger,
    {
        pub fn new(messenger: &'a T, max: usize) -> LimitTracker<'a, T> {
            LimitTracker {
                messenger,
                value: 0,
                max,
            }
        }

        pub fn set_value(&mut self, value: usize) {
            self.value = value;

            let percentage_of_max = self.value as f64 / self.max as f64;

            if percentage_of_max >= 1.0 {
                self.messenger.send("Error: You are over your quota!");
            } else if percentage_of_max >= 0.9 {
                self.messenger
                    .send("Urgent warning: You've used up over 90% of your quota!");
            } else if percentage_of_max >= 0.75 {
                self.messenger
                    .send("Warning: You've used up over 75% of your quota!");
            }
        }
    }


    #[cfg(test)]
    mod tests {
        use super::*;

        struct MockMessenger {
            sent_messages: Vec<String>,
        }

        impl MockMessenger {
            fn new() -> MockMessenger {
                MockMessenger {
                    sent_messages: vec![],
                }
            }
        }

        impl Messenger for MockMessenger {
            fn send(&self, message: &str) {
                self.sent_messages.push(String::from(message));
            }
        }

        #[test]
        fn it_sends_an_over_75_percent_warning_message() {
            let mock_messenger = MockMessenger::new();
            let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);

            limit_tracker.set_value(80);

            assert_eq!(mock_messenger.sent_messages.len(), 1);
        }
    }
    ```
    ```rust
        // solution
        pub trait Messenger {
    fn send(&self, msg: &str);
    }

    pub struct LimitTracker<'a, T: Messenger> {
        messenger: &'a T,
        value: usize,
        max: usize,
    }

    impl<'a, T> LimitTracker<'a, T>
    where
        T: Messenger,
    {
        pub fn new(messenger: &'a T, max: usize) -> LimitTracker<'a, T> {
            LimitTracker {
                messenger,
                value: 0,
                max,
            }
        }

        pub fn set_value(&mut self, value: usize) {
            self.value = value;

            let percentage_of_max = self.value as f64 / self.max as f64;

            if percentage_of_max >= 1.0 {
                self.messenger.send("Error: You are over your quota!");
            } else if percentage_of_max >= 0.9 {
                self.messenger
                    .send("Urgent warning: You've used up over 90% of your quota!");
            } else if percentage_of_max >= 0.75 {
                self.messenger
                    .send("Warning: You've used up over 75% of your quota!");
            }
        }
    }


    #[cfg(test)]
    mod tests {
        use std::cell::RefCell;
        use super::*;

        struct MockMessenger {
            sent_messages: RefCell<Vec<String>>,
        }

        impl MockMessenger {
            fn new() -> MockMessenger {
                MockMessenger {
                    sent_messages: RefCell::new(vec![]),
                }
            }
        }

        impl Messenger for MockMessenger {
            fn send(&self, message: &str) {
                self.sent_messages.borrow_mut().push(String::from(message));
            }
        }

        #[test]
        fn it_sends_an_over_75_percent_warning_message() {
            let mock_messenger = MockMessenger::new();
            let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);

            limit_tracker.set_value(80);

            assert_eq!(mock_messenger.sent_messages.borrow().len(), 1);
        }
    }

    ```

5. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    pub trait Messenger {
    fn send(&self, msg: &str);
    }

    pub struct LimitTracker<'a, T: Messenger> {
        messenger: &'a T,
        value: usize,
        max: usize,
    }

    impl<'a, T> LimitTracker<'a, T>
    where
        T: Messenger,
    {
        pub fn new(messenger: &'a T, max: usize) -> LimitTracker<'a, T> {
            LimitTracker {
                messenger,
                value: 0,
                max,
            }
        }

        pub fn set_value(&mut self, value: usize) {
            self.value = value;

            let percentage_of_max = self.value as f64 / self.max as f64;

            if percentage_of_max >= 1.0 {
                self.messenger.send("Error: You are over your quota!");
            } else if percentage_of_max >= 0.9 {
                self.messenger
                    .send("Urgent warning: You've used up over 90% of your quota!");
            } else if percentage_of_max >= 0.75 {
                self.messenger
                    .send("Warning: You've used up over 75% of your quota!");
            }
        }
    }


    #[cfg(test)]
    mod tests {
        use super::*;
        use std::cell::RefCell;

        struct MockMessenger {
            sent_messages: RefCell<Vec<String>>,
        }

        impl MockMessenger {
            fn new() -> MockMessenger {
                MockMessenger {
                    sent_messages: RefCell::new(vec![]),
                }
            }
        }

        impl Messenger for MockMessenger {
            fn send(&self, message: &str) {
                let mut one_borrow = self.sent_messages.borrow_mut();
                let mut two_borrow = self.sent_messages.borrow_mut();

                one_borrow.push(String::from(message));
                two_borrow.push(String::from(message));
            }
        }

        #[test]
        fn it_sends_an_over_75_percent_warning_message() {
            let mock_messenger = MockMessenger::new();
            let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);

            limit_tracker.set_value(80);

            assert_eq!(mock_messenger.sent_messages.borrow().len(), 1);
        }
    }
    ```
    - Proizvodi je i to u funkciji send jer refcell omogucava samo jednog vlasnika. A u njoj pokusavamo da imamo 2.

6. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
        let add_one_v4 = |x|  x + 1;
    }

    // solution
    fn main() {
        let add_one_v4 = |x: u32| -> u32  {x + 1};
    }
    ```

7. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
        let example_closure = |x| x;

        let s = example_closure(String::from("hello"));
        let n = example_closure(5);
    }
    ```

    - Da, ovaj kod će proizvesti grešku. Razlog tome je što Rust inferiše tipove za zatvarajuće funkcije (closures) na osnovu prvog puta kada se koriste. U ovom slučaju, prvi put kada se example_closure koristi, pretpostavljeni tip parametra x postaje tip String, 

8. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
        fn main() {
        let list = vec![1, 2, 3];
        println!("Before defining closure: {:?}", list);

        let only_borrows = || println!("From closure: {:?}", list);

        println!("Before calling closure: {:?}", list);
        only_borrows();
        println!("After calling closure: {:?}", list);
    }
    ```
    - Ne proizvodi gresku jer zatvarajuca funkcija koristi samo nepromenljive reference na vlasnika list a ne mutabilne.

9. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
        let mut list = vec![1, 2, 3];
        println!("Before defining closure: {:?}", list);

        let mut borrows_mutably = || list.push(7);
        println!("Before calling closure: {:?}", list);
        borrows_mutably();
        println!("After calling closure: {:?}", list);
    }
    ```
    - Hoce jer imamo i promenljive i nepromenljive reference.

10. Ispravi grešku u sledećem kodu:

    ```rust
    use std::thread;

    fn main() {
        let list = vec![1, 2, 3];
        println!("Before defining closure: {:?}", list);

        thread::spawn(|| println!("From thread: {:?}", list))
            .join()
            .unwrap();
        // resenje
         thread::spawn(move || println!("From thread: {:?}", list))
            .join()
            .unwrap();
    }
    ```

11. U zavisnosti od zapamćene vrednosti u zatvorenju, koje tri `Fn` osobine zatvorenje može da implementira?
    - 
    1. FnOnce - затворења која могу да се позову једном. Сва затворења имплементирају бар ову особину, пошто могу да се позову бар једном. Затворења која предају власништво запамћене вредности приликом позива имплементрају само ову особину пошто се не могу позвати више од једном.
    2. FnMut - затворења која не премештају вредности али их могу мењати. Могу се позвати више од једном.
    3. Fn - затворења која нити премештају нити мењају своје окружење, или не памте ништа из окружења. Могу се позвати више пута.
12. Koju `Fn` osobinu implementiraju svi tipovi zatvorenja?
    - FnOnce
13. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    #[derive(Debug)]
    struct Rectangle {
        width: u32,
        height: u32,
    }

    fn main() {
        let mut list = [
            Rectangle { width: 10, height: 1 },
            Rectangle { width: 3, height: 5 },
            Rectangle { width: 7, height: 12 },
        ];

        let mut sort_operations = vec![];
        let value = String::from("by key called");

        list.sort_by_key(|r| {
            sort_operations.push(value);
            r.width
        });
        println!("{:#?}", list);
    }
    - Proizvesce gresku zato sto imamo zatvorenje koje radi premestanje iz okruzenja i time je FnOnce.
    ```

14. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    #[derive(Debug)]
    struct Rectangle {
        width: u32,
        height: u32,
    }

    fn main() {
        let mut list = [
            Rectangle { width: 10, height: 1 },
            Rectangle { width: 3, height: 5 },
            Rectangle { width: 7, height: 12 },
        ];

        let mut num_sort_operations = 0;
        list.sort_by_key(|r| {
            num_sort_operations += 1;
            r.width
        });
        println!("{:#?}, sorted in {num_sort_operations} operations", list);
    }
    -Nece jer je sada zatvorenje FnMut
    ```

15. Da li su iteratori "lenji" u Rust-u?
    - Итератори у Расту су "лењи", односно процесирање ће се одложити и обавити тек онда када је то заиста потребно.
16. Šta predstavlja `Iterator` osobina?
    - Ова особина има придружени тип (associated type) - type Item односно Self::Item. Стога, имплементација ове особине над неким типом захтева дефиницију и придруженог типа који представља тип елемената над којима се врши итерација.
17. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
        let v1 = vec![1, 2, 3];

        let v1_iter = v1.iter();
        //resenje
        let mut v1_iter = v1.iter();
        //

        assert_eq!(v1_iter.next(), Some(&1));
        assert_eq!(v1_iter.next(), Some(&2));
        assert_eq!(v1_iter.next(), Some(&3));
        assert_eq!(v1_iter.next(), None);
    }
    ```

18. Ispravi grešku u sledećem kodu:

    ```rust
    fn main() {
        let v1 = vec![1, 2, 3];

        let mut v1_iter = v1.iter();
        
        let mut first = v1_iter.next().unwrap();
        first += 1;
    }
    // solution 
    fn main() {
        let v1 = vec![1, 2, 3];

        let mut v1_iter = v1.iter();
        
        let mut first = v1_iter.next().unwrap();
        first += 1;
    }
    ```
    
19. Šta su konzumirajući adapteri (Engl. consuming adapters)?
    - To su metode koje vrse konzumaciju iteratora(next metodom).
20. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn main() {
        let v1 = vec![1, 2, 3];

        let v1_iter = v1.iter();

        let total: i32 = v1_iter.sum();

        assert_eq!(total, 6);
        
        let give_me_next_pls = v1_iter.next();
    }
    
    ```
    - - Proizvodi jer je sum metoda konzumirajuca pa posle poziva sum metode vise nismo u stanju da pozovemo v1_iter jer smo ga konzumirali.
21. Šta su iterator adapteri (Engl. iterator adapters)?
    - To su metode koje proizvode druge iteratore i vrse konverziju jednog iteratora u neki drugi
    npr: v1.iter().map(|x| x + 1);
22. Ispravi grešku u sledećem kodu:

```rust
    fn main() {
        let v1: Vec<i32> = vec![1, 2, 3];
        let v2 = v1.iter().map(|x| x + 1).collect();
        // resenje
        let v2: Vec<i32> = ...;
        assert_eq!(v2, vec![2, 3, 4]);
    }
```

23. Ispravi grešku u sledećem kodu:

    ```rust
    #[derive(PartialEq, Debug)]
    struct Shoe {
        size: u32,
        style: String,
    }

    fn shoes_in_size(shoes: Vec<Shoe>, shoe_size: u32) -> Vec<Shoe> {
        shoes.iter().filter(|s| s.size == shoe_size).collect()
        // resenje
        shoes.into_iter().filter(|s| s.size == shoe_size).collect()

    }

    #[cfg(test)]
    mod tests {
        use super::*;

        #[test]
        fn filters_by_size() {
            let shoes = vec![
                Shoe {
                    size: 10,
                    style: String::from("sneaker"),
                },
                Shoe {
                    size: 13,
                    style: String::from("sandal"),
                },
                Shoe {
                    size: 10,
                    style: String::from("boot"),
                },
            ];

            let in_my_size = shoes_in_size(shoes, 10);

            assert_eq!(
                in_my_size,
                vec![
                    Shoe {
                        size: 10,
                        style: String::from("sneaker")
                    },
                    Shoe {
                        size: 10,
                        style: String::from("boot")
                    },
                ]
            );
        }
    }
    ```

24. Pri dodeli drugoj varijabli, da li Rust podrazumevano obavlja kopiranje (`Copy`) varijable?
    - Rust podrazumevano obavlja kopiranje (Copy) varijabli prilikom dodele samo za tipove koji implementiraju Copy trait. Tipovi koji implementiraju Copy su obično jednostavni tipovi podataka poput celih brojeva (i32, u64), karakteri (char), boolean vrednosti (bool), i slično.
25. Da li sledeći kod proizvodi grešku? Zašto?

    ```rust
    fn inc(x: i32) -> i32 {
        x + 1
    }

    fn main() {
        let x = 5;
        let y = inc(x);
        println!("{x}, {y}");
    }
    ```
    - Ne prozivodi jer je x prost tip pa kopiranje nije problem.

26. Napiši koncizniji kod umesto sledećeg koda upotrebom iterator adaptera i `filter` metode.

    ```rust
    pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
        let mut results = Vec::new();

        for line in contents.lines() {
            if line.contains(query) {
                results.push(line);
            }
        }

        results
    }
    // solution
    pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
        contents
        .lines()
        .filter(|line| line.contains(query))
        .collect()
    }
    ```
