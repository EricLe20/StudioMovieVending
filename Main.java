import java.util.*;

public class Main {
    // -------------- Movie Class ----------------
    static class Movie {
        private String title, actor, actress, genre;
        private int year, stock, rented, purchased;
        private double price;

        public Movie(String title, String actor, String actress, int year, String genre, int stock, double price) {
            this.title = title; this.actor = actor; this.actress = actress;
            this.year = year; this.genre = genre;
            this.stock = stock; this.price = price; this.rented = 0; this.purchased = 0;
        }
        public Movie(String title) { this(title, "", "", 0, "", 0, 0.0); }
        // Getters and setters omitted for brevity...
        public String getTitle() { return title; }
        public String getActor() { return actor; }
        public String getActress() { return actress; }
        public int getYear() { return year; }
        public String getGenre() { return genre; }
        public int getStock() { return stock; }
        public double getPrice() { return price; }
        public void setTitle(String t) { this.title = t; }
        public void setActor(String a) { this.actor = a; }
        public void setActress(String a) { this.actress = a; }
        public void setYear(int y) { this.year = y; }
        public void setGenre(String g) { this.genre = g; }
        public void setPrice(double p) { this.price = p; }
        public void setStock(int s) { this.stock = s; }
        public void rentMovie() { if(stock>0){ stock--; rented++; System.out.println("Rented: "+title); } else System.out.println("Out of stock."); }
        public void purchaseMovie() { if(stock>0){ stock--; purchased++; System.out.println("Purchased: "+title); } else System.out.println("Out of stock."); }
        public void restock(int amt) { stock += amt; }
        public int getRented() { return rented; }
        public int getPurchased() { return purchased; }
        public String toString() {
            return title + " (" + year + ") - " + genre + "\nActor: " + actor + ", Actress: " + actress +
                    "\nStock: " + stock + ", Price: $" + price;
        }
    }

    // --------- Inventory Class using ArrayList<Movie> --------------
    static class Inventory {
        // THIS IS THE ARRALIST!
        private ArrayList<Movie> movies;
        public Inventory() { movies = new ArrayList<>(); }
        public void addMovie(Movie m) { movies.add(m); }
        public void removeMovie(String title) { movies.removeIf(m -> m.getTitle().equalsIgnoreCase(title)); }
        public Movie findMovie(String title) {
            for (Movie m : movies) if (m.getTitle().equalsIgnoreCase(title)) return m;
            return null;
        }
        public ArrayList<Movie> search(String keyword) {
            ArrayList<Movie> res = new ArrayList<>();
            keyword = keyword.toLowerCase();
            for (Movie m : movies) {
                if (m.getTitle().toLowerCase().contains(keyword) ||
                        m.getActor().toLowerCase().contains(keyword) ||
                        m.getActress().toLowerCase().contains(keyword) ||
                        m.getGenre().toLowerCase().contains(keyword) ||
                        Integer.toString(m.getYear()).equals(keyword)
                ) res.add(m);
            }
            return res;
        }
        public void sortMovies(boolean az) {
            movies.sort(Comparator.comparing(Movie::getTitle));
            if(!az) Collections.reverse(movies);
        }
        public void displayMovies(List<Movie> list) {
            if(list.isEmpty()) { System.out.println("No movies found."); return;}
            for(Movie m : list) { System.out.println(m.toString()); System.out.println("-------------------"); }
        }
        public void displayAllMovies() { displayMovies(movies); }
        public void restockMovie(String title, int amt) {
            Movie m = findMovie(title); if(m!=null && amt > 0) m.restock(amt);
        }
        public void updateMovieInfo(String title, Scanner sc) {
            Movie m = findMovie(title); if(m==null) return;
            System.out.println("Edit (blank to skip):");
            System.out.print("New Title: "); String s = sc.nextLine(); if(!s.trim().isEmpty()) m.setTitle(s);
            System.out.print("New Actor: "); s = sc.nextLine(); if(!s.trim().isEmpty()) m.setActor(s);
            System.out.print("New Actress: "); s = sc.nextLine(); if(!s.trim().isEmpty()) m.setActress(s);
            System.out.print("New Year: "); s = sc.nextLine(); if(!s.trim().isEmpty()) m.setYear(Integer.parseInt(s));
            System.out.print("New Genre: "); s = sc.nextLine(); if(!s.trim().isEmpty()) m.setGenre(s);
            System.out.print("New Price: "); s = sc.nextLine(); if(!s.trim().isEmpty()) m.setPrice(Double.parseDouble(s));
        }
        public void showRentalsAndPurchases() {
            System.out.println("Rentals & Purchases:");
            for(Movie m : movies)
                System.out.printf("%s - Rented: %d, Purchased: %d\n", m.getTitle(), m.getRented(), m.getPurchased());
        }
    }

    static class Manager {
        private String username = "admin", password = "password";
        public boolean login(String u, String p) { return username.equals(u) && password.equals(p); }
    }

    // --------- ArrayList of 16 movies ----------
    public static void preloadMovies(Inventory inventory) {
        inventory.addMovie(new Movie("Avengers", "Robert Downey Jr.", "Scarlett Johansson", 2012, "Action", 10, 3.99));
        inventory.addMovie(new Movie("Titanic", "Leonardo DiCaprio", "Kate Winslet", 1997, "Drama", 5, 2.99));
        inventory.addMovie(new Movie("Frozen", "Josh Gad", "Idina Menzel", 2013, "Animation", 7, 2.49));
        inventory.addMovie(new Movie("Inception", "Leonardo DiCaprio", "Ellen Page", 2010, "Sci-Fi", 8, 3.79));
        inventory.addMovie(new Movie("The Matrix", "Keanu Reeves", "Carrie-Anne Moss", 1999, "Sci-Fi", 9, 3.49));
        inventory.addMovie(new Movie("Jurassic Park", "Sam Neill", "Laura Dern", 1993, "Adventure", 6, 2.99));
        inventory.addMovie(new Movie("Star Wars", "Mark Hamill", "Carrie Fisher", 1977, "Sci-Fi", 7, 3.99));
        inventory.addMovie(new Movie("Forrest Gump", "Tom Hanks", "Robin Wright", 1994, "Drama", 10, 3.49));
        inventory.addMovie(new Movie("Toy Story", "Tom Hanks", "Annie Potts", 1995, "Animation", 9, 2.99));
        inventory.addMovie(new Movie("The Lion King", "Matthew Broderick", "Moira Kelly", 1994, "Animation", 12, 2.99));
        inventory.addMovie(new Movie("Shrek", "Mike Myers", "Cameron Diaz", 2001, "Comedy", 8, 3.19));
        inventory.addMovie(new Movie("Avatar", "Sam Worthington", "Zoe Saldana", 2009, "Fantasy", 10, 4.09));
        inventory.addMovie(new Movie("Spider-Man", "Tobey Maguire", "Kirsten Dunst", 2002, "Action", 6, 3.39));
        inventory.addMovie(new Movie("Black Panther", "Chadwick Boseman", "Lupita Nyong'o", 2018, "Action", 8, 4.29));
        inventory.addMovie(new Movie("La La Land", "Ryan Gosling", "Emma Stone", 2016, "Musical", 5, 3.29));
        inventory.addMovie(new Movie("The Godfather", "Al Pacino", "Diane Keaton", 1972, "Crime", 8, 3.89));
        inventory.addMovie(new Movie("Interstellar", "Matthew McConaughey", "Anne Hathaway", 2014, "Sci-Fi", 7, 3.99));
    }

    // ------------- Main ---------------
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Inventory inventory = new Inventory(); // <-- ArrayList in use!
        Manager manager = new Manager();

        // Pre-load 16 sample movies
        preloadMovies(inventory);

        boolean run = true;
        while(run) {
            System.out.println("\nVending Movie Machine");
            System.out.println("1. Manager Mode\n2. User Mode\n3. Exit");
            System.out.print("Select mode: ");
            String input = sc.nextLine().trim();
            switch(input) {
                case "1":
                    System.out.print("Manager Username: ");
                    String u = sc.nextLine();
                    System.out.print("Manager Password: ");
                    String p = sc.nextLine();
                    if(manager.login(u, p)) {
                        boolean mgrMenu = true;
                        while(mgrMenu) {
                            System.out.println("\nManager Menu:");
                            System.out.println("1. Add Movie\n2. Remove Movie\n3. Edit Movie Info\n4. Restock Inventory\n5. View Rentals/Purchases\n6. View All Movies\n7. Logout");
                            System.out.print("Select option: ");
                            String mc = sc.nextLine().trim();
                            switch(mc) {
                                case "1":
                                    System.out.println("Enter movie details:");
                                    System.out.print("Title: "); String t = sc.nextLine().trim();
                                    System.out.print("Actor: "); String actor = sc.nextLine().trim();
                                    System.out.print("Actress: "); String actress = sc.nextLine().trim();
                                    System.out.print("Year: "); int year = Integer.parseInt(sc.nextLine().trim());
                                    System.out.print("Genre: "); String genre = sc.nextLine().trim();
                                    System.out.print("Stock: "); int stock = Integer.parseInt(sc.nextLine().trim());
                                    System.out.print("Price: "); double price = Double.parseDouble(sc.nextLine().trim());
                                    inventory.addMovie(new Movie(t, actor, actress, year, genre, stock, price));
                                    System.out.println("Movie Added.");
                                    break;
                                case "2":
                                    System.out.print("Enter movie title to remove: ");
                                    t = sc.nextLine();
                                    inventory.removeMovie(t);
                                    System.out.println("Movie Removed.");
                                    break;
                                case "3":
                                    System.out.print("Enter movie title to edit: ");
                                    t = sc.nextLine();
                                    inventory.updateMovieInfo(t, sc);
                                    System.out.println("Movie Edited.");
                                    break;
                                case "4":
                                    System.out.print("Enter movie title to restock: ");
                                    t = sc.nextLine();
                                    System.out.print("Enter amount: ");
                                    int amt = Integer.parseInt(sc.nextLine().trim());
                                    inventory.restockMovie(t, amt);
                                    System.out.println("Inventory Restocked.");
                                    break;
                                case "5": inventory.showRentalsAndPurchases(); break;
                                case "6": inventory.displayAllMovies(); break;
                                case "7": mgrMenu = false; break;
                                default: System.out.println("Invalid option.");
                            }
                        }
                    } else System.out.println("Invalid Manager Login.");
                    break;
                case "2":
                    boolean usrMenu = true;
                    while(usrMenu) {
                        System.out.println("\nUser Menu:");
                        System.out.println("1. View All Movies\n2. Search Movies\n3. Sort Movies\n4. Rent Movie\n5. Purchase Movie\n6. Logout");
                        System.out.print("Select option: ");
                        String uc = sc.nextLine().trim();
                        switch(uc) {
                            case "1": inventory.displayAllMovies(); break;
                            case "2":
                                System.out.print("Enter keyword (title, actor, actress, year, genre): ");
                                String key = sc.nextLine();
                                ArrayList<Movie> results = inventory.search(key);
                                inventory.displayMovies(results); break;
                            case "3":
                                System.out.print("Sort A-Z? (y/n): ");
                                String order = sc.nextLine();
                                inventory.sortMovies(order.equalsIgnoreCase("y"));
                                System.out.println("Movies Sorted."); break;
                            case "4":
                                System.out.print("Enter title to rent: ");
                                String rtitle = sc.nextLine();
                                Movie rmovie = inventory.findMovie(rtitle);
                                if(rmovie != null) rmovie.rentMovie(); else System.out.println("Movie not found.");
                                break;
                            case "5":
                                System.out.print("Enter title to purchase: ");
                                String ptitle = sc.nextLine();
                                Movie pmovie = inventory.findMovie(ptitle);
                                if(pmovie != null) pmovie.purchaseMovie(); else System.out.println("Movie not found.");
                                break;
                            case "6": usrMenu = false; break;
                            default: System.out.println("Invalid option.");
                        }
                    }
                    break;
                case "3": run = false; System.out.println("Thanks for using Vending Movie Machine!"); break;
                default: System.out.println("Invalid selection.");
            }
        }
        sc.close();
    }
}