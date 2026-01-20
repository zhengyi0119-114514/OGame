use std::env;
fn main() {
    let target = env::var("TARGET").expect("TARGET environment variable not set");
    println!("Current target: {}", target);
    let shared_library_file_suffix = if target.contains("windows") {
        ".dll"
    } else if target.contains("apple"){
        ".dylib"
    } else{
        ".so"
    };
    
}
