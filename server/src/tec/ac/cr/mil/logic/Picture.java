package tec.ac.cr.mil.logic;

public class Picture {

    public Picture(){}

    public Picture(String name, String author, int year, String pictureData){
        this.name = name;
        this.author = author;
        this.year = year;
        this.pictureData = pictureData;
        this.id = 0;
        this.size = 0;
    }

    private String name;
    private String author;
    private int year;
    private int size;
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

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
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
}
