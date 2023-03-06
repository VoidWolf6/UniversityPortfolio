using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;

public class Buttons : MonoBehaviour
{
    public AudioMixer AM;

    private Color basic;
    public Text info;
    private string into;
    public string pass = "1337";
    public AudioClip beeper;
    public AudioClip right;
    public AudioClip wrong;


    public void Pressed()
    {
        gameObject.GetComponent<AudioSource>().PlayOneShot(beeper, 1);
    }


    public void Number_Click()
    {
        info = GameObject.Find("Monitor").GetComponent<Text>();
        into = gameObject.name;
        
        if (info.text.Length <= 6)
        {
            info.text = info.text + into;
        }
        else
        {
            return;
        }       
    }

    public void Clear_Click()
    {
        GameObject.Find("Monitor").GetComponent<Text>().text = "";
    }

    public void Check_Click()
    {
        basic = GameObject.Find("Bulb").GetComponent<SpriteRenderer>().color;
        if (GameObject.Find("Monitor").GetComponent<Text>().text == pass)
        {
            Clear_Click();
            GameObject.Find("Bulb").GetComponent<SpriteRenderer>().color = Color.green;
            gameObject.GetComponent<AudioSource>().PlayOneShot(right, 1);

        }
        else
        {            
            GameObject.Find("Bulb").GetComponent<SpriteRenderer>().color = Color.red;
            Clear_Click();
            gameObject.GetComponent<AudioSource>().PlayOneShot(wrong, 1);
            GameObject.Find("Bulb").GetComponent<SpriteRenderer>().color = basic;
        }
    }

}
