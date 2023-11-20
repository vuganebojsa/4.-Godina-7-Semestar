// Ispravi grešku u kodu i popuni praznine.
#[derive(Debug)]
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

fn main() {
    let msgs: [Message; 3] = [
        Message::Quit,
        Message::Move{x:1, y:3},
        Message::ChangeColor(255,255,0)
    ];

    for msg in msgs {
        show_message(msg)
    }
} 

fn show_message(msg: Message) {
    match msg{
        Message:: Quit => println!("Quit"),
        Message:: Move{x, y} => println!("Move"),
        Message::Write(s) => println!("Write"),
        Message::ChangeColor(x, y, z) => println!("Ez gays")
    }
}