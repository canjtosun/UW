using System;
using System.Collections.Generic;
using System.IO;
using System.Net;


namespace CanTosun.LWTECH.RealTimeAirplaneStat
{

    class RealTimeAirplaneStatistics
    {
        static void Main(string[] args)
        {
            List<string> typeOfFlights = new List<string>();
            WebClient client = new WebClient();

           
            Console.WriteLine("Airplanes on Air (Regular String Manipulation):");
            Console.WriteLine("======================================");
            
            string line = "";
            string[] tokens = { };

            try
            {
                Stream stream = client.OpenRead("https://public-api.adsbexchange.com/VirtualRadar/AircraftList.json?fTypQN=");

                using (StreamReader reader = new StreamReader(stream))
                {
                    while (!reader.EndOfStream)
                    {
                        line = reader.ReadLine();
                        tokens = line.Split(',');
                    }

                    foreach (string output in tokens)
                    {
                        if (output.Contains("\"Type\""))
                        {
                            string afterProcessTheOutput = output.Substring(7).Replace("\"", "");
                            
                            if (afterProcessTheOutput.StartsWith("B7") && afterProcessTheOutput.Length <= 4) //extracts the 4 letter type code
                            {
                                afterProcessTheOutput = afterProcessTheOutput.Remove(afterProcessTheOutput.Length - 1, 1) + "7";
                                typeOfFlights.Add(afterProcessTheOutput);
                            }

                            else if (afterProcessTheOutput.StartsWith("A3") && afterProcessTheOutput.Length <= 4) //extracts the 4 letter type code
                            {
                                afterProcessTheOutput = afterProcessTheOutput.Remove(afterProcessTheOutput.Length - 1, 1) + "0";
                                typeOfFlights.Add(afterProcessTheOutput);
                            }

                        }
                    }
                }
            }
            catch (IOException ex)
            {
                Console.WriteLine("A network error occurred.  " + ex.Message);
                Console.WriteLine("Unable to continue.");
                return;
            }


            Histogram outputHistogram = new Histogram(typeOfFlights, width: 100, maxLabelWidth: 5);
            outputHistogram.Sort((x, y) => y.Value.CompareTo(x.Value));
            Console.WriteLine(outputHistogram);

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
