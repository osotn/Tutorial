package osotn.gl.com.customlistview;

/**
 * Created by oleksandr.v.sotnikov on 12/23/2015.
 */
public class ListModel {
    private String CompanyName = "";
    private String Image = "";
    private String Url = "";

    /* Set  Methods */

    public void setCompanyName(String CompanyName) {
        this.CompanyName = CompanyName;
    }

    public void setImage(String Image) {
        this.Image = Image;
    }

    public void setUrl(String Url) {
        this.Url = Url;
    }

    /* Get Methods */

    public String getCompanyName() {
        return this.CompanyName;
    }

    public String getImage() {
        return this.Image;
    }

    public String getUrl() {
        return this.Url;
    }
}
