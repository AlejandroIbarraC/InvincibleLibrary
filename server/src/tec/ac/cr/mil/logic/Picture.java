package tec.ac.cr.mil.logic;

public class Picture {

    public Picture(){}

    public Picture(String name, String author, String year){
        this.name = name;
        this.author = author;
        this.year = year;
        this.id = 0;
        this.size = 0;
        this.description = "";
        this.pictureData = "";
    }

    private String name;
    private String author;
    private String year;
    private int size;
    private String description;
    private String pictureData;
    private int id;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getYear() {
        return year;
    }

    public void setYear(String year) {
        this.year = year;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public String getPictureData() {
        return pictureData;
    }

    public void setPictureData(String pictureData) {
        this.pictureData = pictureData;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }
}
