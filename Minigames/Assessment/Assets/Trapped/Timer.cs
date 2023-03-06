using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    public float Remains = 71;
    public bool IsActive = false;
    public Text timeText;
    public AudioMixerSnapshot panik;

     void Start()
    {
        // Starts the timer automatically
        IsActive = true;
    }

    void Update()
    {
        if (IsActive)
        {
            if (Remains > 0)
            {
                Remains -= Time.deltaTime;
                DisplayTime(Remains);
            }
            else
            {
                Debug.Log("Time has run out!");
                Remains = 0;
                IsActive = false;
                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            }
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene("Main Menu");
        }
    }

    void DisplayTime(float displayed)
    {
        displayed += 1;

        float minutes = Mathf.FloorToInt(displayed / 60);
        float seconds = Mathf.FloorToInt(displayed % 60);

        if (Remains <= 30)
        {
            this.GetComponent<Text>().color = Color.red;
            panik.TransitionTo(2);
        }

        timeText.text = string.Format("{0:00}:{1:00}", minutes, seconds);
        
    }
}
