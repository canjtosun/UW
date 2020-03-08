using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Linq;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace RealTimeAirplaneStatistics.wJSON.net
{
    class AircraftProperties
    {
        public string Type { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Airplanes on Air (w/JSON.net):");
            Console.WriteLine("======================================");

            WebClient client = new WebClient();
            string jsonText = "";

            try
            {
                Stream stream = client.OpenRead("https://public-api.adsbexchange.com/VirtualRadar/AircraftList.json?fTypQN=");
                using (StreamReader reader = new StreamReader(stream))
                {
                    jsonText = reader.ReadToEnd();
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine("A network error occurred.  " + ex.Message);
                Console.WriteLine("Unable to continue.");
                return;
            }



            JObject aircraftTypeJO = JObject.Parse(jsonText);
            List<JToken> aircraftTypeJa = aircraftTypeJO["acList"].Children().ToList();

            List<string> aircraftType = new List<string>();
            
            

            foreach (JToken output in aircraftTypeJa)
            {
                AircraftProperties _aircraftProperties = output.ToObject<AircraftProperties>();
                var callType = _aircraftProperties.Type;

                if (_aircraftProperties.Type.StartsWith("B7") && _aircraftProperties.Type.Length <= 4)
                {
                    callType = callType.Remove(_aircraftProperties.Type.Length - 1, 1) + "7";
                    aircraftType.Add(callType);
                }
                else if (_aircraftProperties.Type.StartsWith("A3") && _aircraftProperties.Type.Length <= 4)
                {
                    callType = callType.Remove(_aircraftProperties.Type.Length - 1, 1) + "0";
                    aircraftType.Add(callType);
                }

            }

            Histogram airCraftHistogram = new Histogram(aircraftType, width: 100, maxLabelWidth: 5);
            airCraftHistogram.Sort((x, y) => y.Value.CompareTo(x.Value));
            Console.WriteLine(airCraftHistogram);
            Console.ReadLine();
        }
    }
    class Histogram
    {
        private int width;
        private int maxBarWidth;
        private int maxLabelWidth;
        private int minValue;
        private List<KeyValuePair<string, int>> bars;

        public Histogram(List<string> data, int width = 80, int maxLabelWidth = 10, int minValue = 0)
        {
            this.width = width;
            this.maxLabelWidth = maxLabelWidth;
            this.minValue = minValue;
            this.maxBarWidth = width - maxLabelWidth - 2;   // -2 for the space and pipe separator

            var barCounts = new Dictionary<string, int>();

            foreach (string item in data)
            {
                if (barCounts.ContainsKey(item))
                    barCounts[item]++;
                else
                    barCounts.Add(item, 1);
            }

            this.bars = new List<KeyValuePair<string, int>>(barCounts);

        }

        public void Sort(Comparison<KeyValuePair<string, int>> f)
        {
            bars.Sort(f);
        }

        public override string ToString()
        {
            string s = "";
            string blankLabel = "".PadRight(maxLabelWidth);

            int maxValue = 0;
            foreach (KeyValuePair<string, int> bar in bars)
            {
                if (bar.Value > maxValue)
                    maxValue = bar.Value;
            }

            foreach (KeyValuePair<string, int> bar in bars)
            {
                string key = bar.Key;
                int value = bar.Value;

                if (value >= minValue)
                {
                    string label;
                    if (key.Length < maxLabelWidth)
                        label = key.PadLeft(maxLabelWidth);
                    else
                        label = key.Substring(0, maxLabelWidth);

                    int barSize = (int)(((double)value / maxValue) * maxBarWidth);
                    string barStars = "".PadRight(barSize, '*');

                    s += label + " |" + barStars + " " + value + "\n";
                }
            }

            string axis = blankLabel + " +".PadRight(maxBarWidth + 2, '-') + "\n";    //TODO: Why is +2 is needed?
            s += axis;

            return s;
        }
    }
}
