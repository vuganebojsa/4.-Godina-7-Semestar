// Ispravi grešku u kodu i popuni praznine.
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

fn main() {
    let msg = Message::Move{x: 1, y: 2};

    if let Message::Move{x, y} = msg {
        assert_eq!(x, 1);
        assert_eq!(y, 2);
    } else {
        panic!("Ne dozvoli da se ova sekcija izvrši！");
    }

    println!("Success!");
} 
