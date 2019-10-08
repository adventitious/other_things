using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

/*
    author      : Cathal McGivney
    date        : 16 / May / 2019
    description : Read ticket types from file, total and display in table
 */

namespace exammay
{
    class Question1
    {
        string[] ticketTypes = { "Basic", "Super", "Delux", "VIP" };
        int[] ticketPrices   = { 40, 45, 55, 60 };
        int[] ticketCounter  = { 0, 0, 0, 0 };

        public Question1()
        {
            Console.WriteLine("\n");
            ReadFile();
            PrintTable();
        }


        void ReadFile()
        {
            // Read text file and send contents of each line to be processed

            FileStream fs = null;
            try
            {
                fs = new FileStream("ticketsales.txt", FileMode.Open);
            }
            catch (Exception e)
            {
                Console.WriteLine("file could not be opened, " + e.Message);
                return;
            }

            StreamReader sr = new StreamReader(fs);
            string lineIn = sr.ReadLine();

            while (lineIn != null)
            {
                // Print out contents of each line
                // Console.WriteLine("> {0}", lineIn);

                string[] parts = lineIn.Split(',');
                addTicketSale(parts);
                lineIn = sr.ReadLine();
            }

        }


        void addTicketSale(string[] parts)
        {
            // A line, as an array of strings, is processed

            if (parts.Length != 3)
            {
                return;
            }

            string ticketType = parts[1];
            int ticketAmount = 0;

            // parse integer from string, if fails exit method
            try
            {
                ticketAmount = int.Parse(parts[2]);
            }
            catch( Exception e )
            {
                Console.WriteLine("error parsing integer, " + e.Message);
                return;
            }

            // what type of tickets does line refer to, add info to appropriate counter
            for (int i = 0; i < ticketTypes.Length; i++)
            {
                if (ticketType == ticketTypes[i])
                {
                    ticketCounter[i] = ticketCounter[i] + ticketAmount;
                    i = ticketTypes.Length; // exit for loop
                }
            }
        }


        void PrintTable()
        {
            string space30 = "------------------------------";
            string spaces = " " + space30 + space30 + "----------------";

            // print a horizontal line
            Console.WriteLine(spaces);

            // print table headings
            Console.WriteLine(" | {0,-23}| {1,-23}| {2,-23}|", "Ticket Type", "Tickets Sold", "Total Retail Value");

            Console.WriteLine(spaces);

            int ticketsTotal = 0;
            int retailValueTotal = 0;

            // print each ticket types values
            for (int i = 0; i < ticketTypes.Length; i++)
            {
                int retailValue = ticketPrices[i] * ticketCounter[i];

                Console.WriteLine(" | {0,-23}|{1,23} |{2,23:0,0.00} |", ticketTypes[i], ticketCounter[i], retailValue );
                ticketsTotal = ticketsTotal + ticketCounter[i];
                retailValueTotal = retailValueTotal + retailValue;
            }
            // print totals
            Console.WriteLine(" | {0,-23}|{1,23} |{2,23:0,0.00} |", "Total", ticketsTotal, retailValueTotal);

            Console.WriteLine(spaces);

            Console.WriteLine();
        }
    }
}
