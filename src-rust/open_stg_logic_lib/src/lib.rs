#[unsafe(export_name = "OgLgAdd")]
pub extern "C" fn add(f: i32, s: i32) -> i32 {
    f + s
}
