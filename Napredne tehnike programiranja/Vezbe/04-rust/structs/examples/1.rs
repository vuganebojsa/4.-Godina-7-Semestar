// Ispravi grešku u kodu.
struct Person {
    name: String,
    age: u8,
    hobby: String
}
fn main() {
    let age = 30;
    let p = Person {
        name: String::from("student"),
        age,
        hobby: String::from("student")
    };

    println!("Success!");
} 
