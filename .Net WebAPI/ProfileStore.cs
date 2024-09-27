using WebApi.Models;

namespace WebApi.DataStore;

public class ProfileStore
{
    public static List<ProfileModel> profileList= new List<ProfileModel>
    {
        new ProfileModel{Name="Krishna Kumar B",
        DOB="09-070-2002",
        Qualification="B.Tech Computer Science and Business Systems",
        College="Sri Sairam Engineering College",
        Passout="2024",
        Email="krish.lk75@gmail.com",
        Place="Thiruvallur"}
    };
}
