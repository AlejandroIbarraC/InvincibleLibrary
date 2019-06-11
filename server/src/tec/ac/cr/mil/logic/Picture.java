package tec.ac.cr.mil.logic;

public class Picture {

    public Picture(){}

    public Picture(String name, String autor, int year, int size, String pictureData){
        this.name = name;
        this.autor = autor;
        this.year = year;
        this.size = size;
        this.pictureData = pictureData;
    }

    private String name;
    private String autor;
    private int year;
    private int size;
    private String pictureData;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAutor() {
        return autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
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
}
