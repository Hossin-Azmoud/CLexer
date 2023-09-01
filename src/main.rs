use std::io;
use std::io::prelude::*;
use std::fs::File;

fn main() -> io::Result<()> {
    let mut f      = File::open("source")?;
    let mut buffer = [0; 1];

    f.read(&mut buffer)?;
    for i in 0..1 {
        println!("{}", (buffer[i] as char));
    }

    Ok(())
}
