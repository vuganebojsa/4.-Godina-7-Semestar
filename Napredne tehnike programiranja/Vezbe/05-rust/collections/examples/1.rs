// Popuni praznine i ispravi greške u kodu.
// 1. Nemoj koristiti `to_string()`
// 2. Nemoj dodavati ili uklanjati redove
fn main() {
    let mut s: String = String::from("hello, ");
    s.push_str("world");
    s.push('!');

    move_ownership(s.clone());

    assert_eq!(s, "hello, world!");

    println!("Success!");
}

fn move_ownership(s: String) {
    println!("ownership of \"{}\" is moved here!", s)
}
