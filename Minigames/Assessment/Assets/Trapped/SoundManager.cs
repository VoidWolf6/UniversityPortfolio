using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{

    public enum SFXType { };
    public List<AudioClip> ClipList = new List<AudioClip>();
    private Dictionary<SFXType, AudioClip> SFX_Lib = new Dictionary<SFXType, AudioClip>();

    void Start()
    {
        //for (int i = 0; i < SFXType.GetNames(typeof(SFXType).Length; i++)
        //{

        //}
    }

   
}
