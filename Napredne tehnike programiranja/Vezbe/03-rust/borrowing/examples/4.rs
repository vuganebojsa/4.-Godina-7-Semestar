fn main() {
    let s = String::from("hello, ");

    let mut p = s; // TODO
    
    p.push_str("world");

    println!("Success!");
}