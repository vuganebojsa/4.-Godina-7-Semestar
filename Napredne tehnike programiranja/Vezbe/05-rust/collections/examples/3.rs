// Izmeni sledeći kod tako da se ispiše: 
// 25
// 25
// 25
fn main() {
    let mut s = String::with_capacity(25);

    println!("{}", s.capacity());

    for _ in 0..2 {
        println!("{}", s.capacity());
    }

    println!("Success!");
}
