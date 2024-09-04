use std::io;

use ratatui::crossterm::event;
use ratatui::crossterm::event::{Event, KeyCode};

use crate::app::App;
use crate::tui::Tui;
use crate::ui::ui;

mod app;
mod tui;
mod ui;

fn main() -> io::Result<()> {
    let mut term = tui::init()?;
    let mut app = App::default();
    run(&mut app, &mut term)?;
    tui::restore()?;
    Ok(())
}
fn run(app: &mut App, term: &mut Tui) -> io::Result<()> {
    loop {
        term.draw(|f| ui(f, app))?;
        if let Event::Key(key) = event::read()? {
            if key.code == KeyCode::Char('q') {
                return Ok(());
            }
        }
    }

    Ok(())
}
