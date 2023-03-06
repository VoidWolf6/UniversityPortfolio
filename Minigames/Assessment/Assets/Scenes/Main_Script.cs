using UnityEngine;
using UnityEngine.SceneManagement;

public class Main_Script : MonoBehaviour
{
    public GameObject[] scenes;


    public void Bring()
    {
        SceneManager.LoadScene(gameObject.name, LoadSceneMode.Additive);

        scenes = GameObject.FindGameObjectsWithTag("Scene");
        foreach (var item in scenes)
        {
            item.SetActive(false);
        }
    }

}
