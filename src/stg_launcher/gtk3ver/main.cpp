#include <gtk/gtk.h>
#include <fstream>

static void launchOGame(GtkWidget *widget,gpointer data)
{
    g_print("Launch Game\n");
}
static void exitProgram()
{
    gtk_main_quit();
    exit(EXIT_SUCCESS);
}
int main(int argc, char *args[])
{
    std::fstream s{"",std::fstream::in};
    gtk_init(&argc, &args);

    GtkWidget *pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *pNoteBook = gtk_notebook_new();
    GtkWidget *pLaunchButton = gtk_button_new_with_label("Launch ogame!");
    GtkWidget *pPage1 = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    GtkWidget *pInformationLable = gtk_label_new("");

    gtk_window_set_title(GTK_WINDOW(pWindow),"傻逼");
    gtk_window_set_default_size(GTK_WINDOW(pWindow),1200,675);
    g_signal_connect(pWindow,"destory",G_CALLBACK(exitProgram),NULL);

    gtk_container_add(GTK_CONTAINER(pWindow),pNoteBook);

    //Page1

    gtk_main();
    return EXIT_SUCCESS;
}