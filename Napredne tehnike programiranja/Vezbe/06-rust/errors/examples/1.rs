// Popuni prazna mesta i ispravi greške
use std::num::ParseIntError;

fn multiply(n1_str: &str, n2_str: &str) -> Result<i32, ParseIntError> {
    let n1 = n1_str.parse::<i32>();
    let n2 = n2_str.parse::<i32>();
    
    let n1n = match n1{
        Ok(n1nn) => n1nn,
        Err(e) => return Err(e)
    };

    let n2n = match n2{
        Ok(n2nn) => n2nn,
        Err(e) => return Err(e)
    };

    Ok(n1n * n2n)
}

fn main() {
    let result = multiply("10", "2");
    assert_eq!(result, Ok(20));

    let result = multiply("t", "2");
    assert!(result.is_err());

    println!("Success!");
}
