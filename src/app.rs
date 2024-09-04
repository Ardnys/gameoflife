pub struct App {
    grid: [bool; 50 * 50],
}
impl Default for App {
    fn default() -> Self {
        App::new()
    }
}
impl App {
    fn new() -> Self {
        App {
            grid: [false; 50 * 50],
        }
    }
}
