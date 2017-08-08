#include "Grid.h"

Grid *Grid::New()
{
    return (Grid *)gtk_grid_new();
}

GtkBaselinePosition Grid::baselinePosition(int row) const { return gtk_grid_get_row_baseline_position(GTK_GRID(this), row); }

void Grid::baselinePosition(GtkBaselinePosition rs, int row) { gtk_grid_set_row_baseline_position(GTK_GRID(this), row, rs); }
int Grid::baselineRow() const { return gtk_grid_get_baseline_row(GTK_GRID(this)); }
void Grid::baselineRow(int rs) { gtk_grid_set_baseline_row(GTK_GRID(this), rs); }
bool Grid::columnHomogeneous() const { return gtk_grid_get_column_homogeneous(GTK_GRID(this)); }
void Grid::columnHomogeneous(bool rh) { gtk_grid_set_column_homogeneous(GTK_GRID(this), rh); }
uint Grid::columnSpacing() const { return gtk_grid_get_column_spacing(GTK_GRID(this)); }
void Grid::columnSpacing(uint rs) { gtk_grid_set_column_spacing(GTK_GRID(this), rs); }
bool Grid::rowHomogeneous() const { return gtk_grid_get_row_homogeneous(GTK_GRID(this)); }
void Grid::rowHomogeneous(bool rh) { gtk_grid_set_row_homogeneous(GTK_GRID(this), rh); }
uint Grid::rowSpacing() const { return gtk_grid_get_row_spacing(GTK_GRID(this)); }
void Grid::rowSpacing(uint rs) { gtk_grid_set_row_spacing(GTK_GRID(this), rs); }

void Grid::Attach(BaseWidget *widget, int left, int top, int width, int height) { gtk_grid_attach(GTK_GRID(this),  GTK_WIDGET(widget), left, top, width, height); }
void Grid::AttachNextTo(BaseWidget *child, BaseWidget *sibling, GtkPositionType side, int width, int height) { gtk_grid_attach_next_to(GTK_GRID(this),  GTK_WIDGET(child),  GTK_WIDGET(sibling), side, width, height); }
BaseWidget *Grid::GetChildAt(int left, int top) { return (BaseWidget *)gtk_grid_get_child_at(GTK_GRID(this), left, top); }
void Grid::InsertColumn(int position) { gtk_grid_insert_column(GTK_GRID(this), position); }
void Grid::InsertNextTo(BaseWidget *sibling, GtkPositionType side) { gtk_grid_insert_next_to(GTK_GRID(this),  GTK_WIDGET(sibling), side); }
void Grid::InsertRow(int position) { gtk_grid_insert_row(GTK_GRID(this), position); }
void Grid::RemoveColumn(int position) { gtk_grid_remove_column(GTK_GRID(this), position); }
void Grid::RemoveRow(int position) { gtk_grid_remove_row(GTK_GRID(this), position); }
