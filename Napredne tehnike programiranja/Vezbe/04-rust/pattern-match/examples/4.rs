// Popuni praznine.
enum Message {
    Write(String),
}

fn main() {
    let a = Message::Write(String::from("This is a message"));

    if let Message::Write(i) = a {
        println!("message holds the value: {}", i);

        println!("Success!");
    }
}