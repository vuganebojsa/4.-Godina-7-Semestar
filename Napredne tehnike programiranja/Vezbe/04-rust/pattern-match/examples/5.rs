
fn main() {}
// Simbol | se koristi za podudaranje više vrednosti, dok se ..= koristi za podudaranje inkluzivnog opsega.
fn match_number(n: i32) {
    let ninf = std::f64::NEG_INFINITY;
    let inf = std::f64::INFINITY;
    match n {
        // Podudaranje jedne vrednosti
        1 => println!("One!"),
        // Popuni prazninu sa `|`
        2 | 3 | 4 | 5 => println!("match 2 -> 5"),
        // Podudaranje inkluzivnog opsega
        6..=10 => {
            println!("match 6 -> 10")
        },
        (-1111111..=0) | (11..=111111) => {
            println!("match -infinite -> 0 or 11 -> +infinite")
        },
        other =>{println!("Blatruc")}
    }
}
