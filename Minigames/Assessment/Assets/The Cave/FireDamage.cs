using UnityEngine;

public class FireDamage : MonoBehaviour
{
    public GameObject Player;
    private GameObject graphical;

    private float CurrentTimer;
    public float BurnInterval = 1;
    
    public float Health = 15;
    public int Fire;
    public float FireTicks = 6;
    private float CurrentFireTicks;
    public bool OnFire;


    public float RoomInterval = 0.5f;
    public int DOT_DEBUFF; 
    // Start is called before the first frame update
    void Start()
    {
        CurrentFireTicks = FireTicks;
        OnFire = false;
        graphical = GameObject.Find("FireTrap");
    }

    // Update is called once per frame
    void Update()
    {
        Fire = Random.Range(1, 4);
    }

    private void OnTriggerStay2D(Collider2D room)
    {
        if (room.transform.name == "Third")
        {
            graphical.GetComponent<ParticleSystem>().Play();
            Debug.Log("Warning: Fire");
        }
            if (!OnFire)
            {
                CurrentTimer += Time.deltaTime;
                if (CurrentTimer > RoomInterval)
                {
                    DOT_DEBUFF += 1;
                    CurrentTimer = 0;
                }
            }
            if (DOT_DEBUFF == 10)
            {
                OnFire = true;
            }
              

        if (OnFire)
        {
            Debug.Log("ON FIRE!!");
            CurrentTimer += Time.deltaTime;

            if (CurrentTimer > BurnInterval)
            {
                CurrentFireTicks--;
                Health -= Fire;
                CurrentTimer = 0;
                OnFire = !(CurrentFireTicks == 0);
            }

            if (Health <= 0)
            {
                Player.GetComponent<UsefulScript>().KillPlayer();
            }
            else if (CurrentFireTicks == 0)
            {
                DOT_DEBUFF = 0;
            }
        }
    }

    private void OnTriggerExit2D(Collider2D room)
    {
        if (room.transform.name == "Third")
        {
            graphical.GetComponent<ParticleSystem>().Stop();
        }
    }
}
