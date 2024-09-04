use ratatui::Frame;
use ratatui::layout::Alignment::Center;
use ratatui::layout::Constraint::{Min, Percentage};
use ratatui::layout::Direction::{Horizontal, Vertical};
use ratatui::layout::Layout;
use ratatui::style::Style;
use ratatui::widgets::{Block, Borders};

use crate::app::App;

fn create_block(title: &str) -> Block {
    Block::default()
        .borders(Borders::all())
        .style(Style::default())
        .title(title)
        .title_alignment(Center)
}

pub fn ui(frame: &mut Frame, app: &mut App) {
    let [game_layout, side_panel_layout] = Layout::default()
        .direction(Horizontal)
        .constraints([Percentage(70), Min(1)])
        .areas(frame.area());

    let rest_block = create_block("Game of Life");

    let [top_layout, bottom_layout] = Layout::default()
        .direction(Vertical)
        .constraints([Percentage(50), Percentage(50)])
        .areas(side_panel_layout);

    let (top_block, bottom_block) = (create_block("top"), create_block("bottom"));

    frame.render_widget(rest_block, game_layout);
    frame.render_widget(top_block, top_layout);
    frame.render_widget(bottom_block, bottom_layout);
}
