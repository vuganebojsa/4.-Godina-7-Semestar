
fn main() {
    let o = Some(7);

    // Iskoristi `if let` sintaksu umesto `match` bloka. 
    if let Some(i) = o {
            println!("This is a really long string and `{:?}`", i);

            println!("Success!");
    }
}