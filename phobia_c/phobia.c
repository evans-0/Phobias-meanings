#include <gtk/gtk.h>

void clicked(GtkWidget *widget, gpointer data)
{
    char *s1 = (char *)gtk_combo_box_get_active_id((GtkComboBox *)data);
    g_print("%s\n", s1);
}

int numLines(FILE *file_obj)
{
    int n = 0;
    char c;
    while ((c = fgetc(file_obj)) != EOF)
    {
        if (c == '\n')
            n++;
    }
    fseek(file_obj, 0, 0);
    return n;
}

int main(int argc, char **argv)
{
    // Reading file
    FILE *fo = fopen("phobias.txt", "r");
    int n = numLines(fo);

    char name[n][40];
    char meaning[n][60];
    char buffer[100];
    for (int i = 0; i<n; i++)
    {
        if (!fgets(buffer, 100, fo))
            break;
        strcpy(name[i], strtok(buffer, "\t"));
        strcpy(meaning[i], strtok(NULL, "\n"));
    }
    fclose(fo);

    // GUI
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *label = gtk_label_new("Select the phobia: ");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    GtkWidget *combo_box = gtk_combo_box_text_new();
    //              grid_identifier,  object  , column, row, colspan, rowspan
    gtk_grid_attach(GTK_GRID(grid), combo_box, 1, 0, 1, 1);

    for (int i = 0; i<n; i++)
    {
        gtk_combo_box_text_append((GtkComboBoxText *)combo_box, meaning[i], name[i]);
    }
    
    GtkWidget *button = gtk_button_new_with_label("OK");
    g_signal_connect(button, "clicked", G_CALLBACK(clicked), (gpointer)combo_box);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);    

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
