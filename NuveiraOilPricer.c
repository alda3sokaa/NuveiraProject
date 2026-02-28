#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_OILS 100

// Global constants
float USD_TO_TL = 43.9f;
const float SUEDE_BAG_COST = 26.5f;
const float CARTON_BAG_COST = 11.3f;
const float PLASTIC_BAG_COST = 1.5f;

const float ETHANOL_100ML_COST = 40.0f;
const float ETHANOL_50ML_COST = 20.0f;
const float ETHANOL_10ML_COST = 4.0f;
const float ETHANOL_5ML_COST = 1.5f;
const float ETHANOL_3ML_COST = 1.0f;

const float BOTTLE_COST_100ML = 100.0f;
const float BOTTLE_COST_50ML = 36.0f;
const float BOTTLE_COST_10ML = 8.5f;
const float BOTTLE_COST_SMALL = 7.0f;

const float STICKER_COST = 4.0f;
const float STICKER_COST_SMALL = 1.0f;

const float LABOR_COST = 35.0f;
const float DEVELOPMENT_COST = 15.0f;
const float DEVELOPMENT_COST_SMALL = 6.0f;

const float SAMPLE_COST = 5.0f;

const float OIL_IN_100ML = 35.0f;
const float OIL_IN_50ML = 18.0f;
const float OIL_IN_10ML = 3.0f;
const float OIL_IN_5ML = 1.8f;
const float OIL_IN_3ML = 1.0f;

const float MARKETING_PERCENTAGE = 1.1f;
const float FAULT_PERCENTAGE = 1.03f;
const float PROFIT_PERCENTAGE = 2.2f;
const float PROFIT_PERCENTAGE_10ML = 2.35f;
const float PROFIT_PERCENTAGE_SMALL = 2.0f;

const float THANK_YOU_CARD = 4.0f;
const float WOMENS_CARD = 3.0f;
const float RAMADAN_CARD = 5.0f;

const float SMALL_BATCH_TAX = 20.0f;
const float MEDIUM_BATCH_TAX = 10.0f;
const float LARGE_BATCH_TAX = 5.0f;


typedef struct Oils {
    char  oil_name[128];
    
    // Input fields
    float oil_price_per_kg_usd;   // price per KG in USD (input)
    float oil_grams;              // grams ordered (input)
    
    // Calculated fields
    float oil_price_per_gram_usd; // after batch adjustments
    float oil_price_per_gram_tl;
    
    float order_price_usd;        // final order price for this oil
    float order_price_tl;
} Oil;

float PriceInUSD(Oil *o);
float Calculate3MLPrice(Oil *o);
float Calculate5MLPrice(Oil *o);
float Calculate10MLPrice(Oil *o);
float Calculate50MLPrice(Oil *o);
float Calculate100MLPrice(Oil *o);
float RoundToNearest50(float price);
float FetchUsdToTlRate(float fallback);
void clearLine(void);

int main(void)
{
    Oil oils[MAX_OILS];
    int NumberOfOils = 0;
    USD_TO_TL = FetchUsdToTlRate(USD_TO_TL); // API used to fetch USD/TL exchange rate whenever the program runs.
    if (USD_TO_TL == 43.9f) {
    printf("Warning: using fallback USD/TL\n");
}
    printf("Live USD/TL: %.4f\n", USD_TO_TL);

    printf("How many oils are you buying?: ");
    if (scanf("%d", &NumberOfOils) != 1) {
        printf("Invalid number.\n");
        return 1;
    }

    if (NumberOfOils < 1 || NumberOfOils > MAX_OILS) {
        printf("Number of oils must be between 1 and %d.\n", MAX_OILS);
        return 1;
    }

    
    for (int i = 0; i < NumberOfOils; i++)
    {
        printf("\n--- Oil #%d ---\n", i + 1);

        printf("Enter oil #%d's name: ", i + 1);

    
    clearLine();

    if (fgets(oils[i].oil_name, sizeof(oils[i].oil_name), stdin) == NULL) {
        printf("Invalid name input.\n");
        return 1;
    }

    // remove trailing newline
    oils[i].oil_name[strcspn(oils[i].oil_name, "\n")] = '\0';

        printf("Enter oil amount in grams: ");
        if (scanf("%f", &oils[i].oil_grams) != 1) {
            printf("Invalid grams input.\n");
            return 1;
        }
        if (oils[i].oil_grams <= 0) {
            printf("Grams must be > 0.\n");
            return 1;
        }

        printf("Enter oil price per KG (USD): ");
        if (scanf("%f", &oils[i].oil_price_per_kg_usd) != 1) {
            printf("Invalid price input.\n");
            return 1;
        }
        if (oils[i].oil_price_per_kg_usd <= 0) {
            printf("Price per KG must be > 0.\n");
            return 1;
        }

        // Calculate pricing for this oil
        if (PriceInUSD(&oils[i]) < 0) {
            printf("Pricing failed for oil #%d.\n", i + 1);
            return 1;
        }
    }

    // Summary
    float totalUSD = 0.0f;
    float totalTL  = 0.0f;

    printf("\n========================\n");
    printf("       ORDER SUMMARY     \n");
    printf("========================\n");

    for (int i = 0; i < NumberOfOils; i++)
    {
        printf("Oil #%d (%s)\n", i + 1, oils[i].oil_name);
        printf("  Grams: %.2f g\n", oils[i].oil_grams);
        printf("  Per gram: %.4f USD | %.4f TL\n",
               oils[i].oil_price_per_gram_usd,
               oils[i].oil_price_per_gram_tl);
        printf("  Oil total: %.2f USD | %.2f TL\n\n",
               oils[i].order_price_usd,
               oils[i].order_price_tl);

        totalUSD += oils[i].order_price_usd;
        totalTL  += oils[i].order_price_tl;
    }

    printf("========================\n");
    printf("TOTAL OILS: %.2f USD | %.2f TL\n", totalUSD, totalTL);
    printf("========================\n");


    printf("\n========================\n");
    printf("RETAIL PRICES\n");
    printf("========================\n");
    for (int i = 0; i < NumberOfOils; i++) {
    float retail = Calculate50MLPrice(&oils[i]);
    float rounded = RoundToNearest50(retail);
    printf("%s -> %.2f TL (Rounded -> %.2f TL)\n", oils[i].oil_name, retail, rounded);
}

    printf("\nPress Enter to exit...");
    getchar();
    getchar();

    return 0;
}

float PriceInUSD(Oil *o)
{
    // Start from input price per KG
    float pricePerKg = o->oil_price_per_kg_usd;

    if (o->oil_grams <= 0) {
        return -1.0f;
    }

    // Batch adjustments (applied to price per KG)
    if (o->oil_grams < 100)
        pricePerKg += SMALL_BATCH_TAX;
    else if (o->oil_grams < 250)
        pricePerKg += MEDIUM_BATCH_TAX;
    else if (o->oil_grams < 500)
        pricePerKg += LARGE_BATCH_TAX;

    // Convert to per gram
    o->oil_price_per_gram_usd = pricePerKg / 1000.0f;
    o->oil_price_per_gram_tl  = o->oil_price_per_gram_usd * USD_TO_TL;

    // Final cost for this oil order
    o->order_price_usd = o->oil_price_per_gram_usd * o->oil_grams;
    o->order_price_tl  = o->order_price_usd * USD_TO_TL;

    return o->order_price_usd;
}
float Calculate100MLPrice(Oil *o)
{
    float RetailPriceInTL;
    float OilAmountPriceInTL;
    OilAmountPriceInTL = OIL_IN_100ML * (o->oil_price_per_gram_tl);

    RetailPriceInTL = (OilAmountPriceInTL + CARTON_BAG_COST + SUEDE_BAG_COST +
                ETHANOL_100ML_COST + BOTTLE_COST_100ML + 
                STICKER_COST + LABOR_COST + DEVELOPMENT_COST + 
                SAMPLE_COST + RAMADAN_CARD + 
                THANK_YOU_CARD) * MARKETING_PERCENTAGE
                * FAULT_PERCENTAGE * PROFIT_PERCENTAGE;
                
    
    return RetailPriceInTL;
    
}
float Calculate50MLPrice(Oil *o)
{
    float RetailPriceInTL;
    float OilAmountPriceInTL;
    OilAmountPriceInTL = OIL_IN_50ML * (o->oil_price_per_gram_tl);

    RetailPriceInTL = (OilAmountPriceInTL + CARTON_BAG_COST + SUEDE_BAG_COST +
                ETHANOL_50ML_COST + BOTTLE_COST_50ML + 
                STICKER_COST + LABOR_COST + DEVELOPMENT_COST + 
                SAMPLE_COST + RAMADAN_CARD + 
                THANK_YOU_CARD) * MARKETING_PERCENTAGE
                * FAULT_PERCENTAGE * PROFIT_PERCENTAGE;
                
    
    return RetailPriceInTL;
    
}
float Calculate10MLPrice(Oil *o)
{
    float RetailPriceInTL;
    float OilAmountPriceInTL;
    OilAmountPriceInTL = OIL_IN_10ML * (o->oil_price_per_gram_tl);

    RetailPriceInTL = (OilAmountPriceInTL + BOTTLE_COST_10ML + ETHANOL_10ML_COST
                        + PLASTIC_BAG_COST + THANK_YOU_CARD + STICKER_COST_SMALL + LABOR_COST
                        + DEVELOPMENT_COST_SMALL) * MARKETING_PERCENTAGE  
                        * FAULT_PERCENTAGE * PROFIT_PERCENTAGE_10ML;

    return RetailPriceInTL;
}
float Calculate5MLPrice(Oil *o)
{
    float RetailPriceInTL;
    float OilAmountPriceInTL;
    OilAmountPriceInTL = OIL_IN_5ML * (o->oil_price_per_gram_tl);

    RetailPriceInTL = (OilAmountPriceInTL + BOTTLE_COST_SMALL + ETHANOL_5ML_COST +
                        + STICKER_COST_SMALL + PLASTIC_BAG_COST + THANK_YOU_CARD
                        + LABOR_COST + DEVELOPMENT_COST_SMALL) * MARKETING_PERCENTAGE
                        * FAULT_PERCENTAGE * PROFIT_PERCENTAGE_SMALL;

    return RetailPriceInTL;
}
float Calculate3MLPrice(Oil *o)
{
    float RetailPriceInTL;
    float OilAmountPriceInTL;
    OilAmountPriceInTL = OIL_IN_3ML * (o->oil_price_per_gram_tl);

    RetailPriceInTL = (OilAmountPriceInTL + BOTTLE_COST_SMALL + ETHANOL_3ML_COST +
                        + STICKER_COST_SMALL + PLASTIC_BAG_COST + THANK_YOU_CARD
                        + LABOR_COST + DEVELOPMENT_COST_SMALL) * MARKETING_PERCENTAGE
                        * FAULT_PERCENTAGE * PROFIT_PERCENTAGE_SMALL;

    return RetailPriceInTL;
}
float RoundToNearest50(float price)
{
    return roundf(price / 50.0f) * 50.0f;
}
float FetchUsdToTlRate(float fallback)
{
    FILE *fp =
#ifdef _WIN32
        _popen("curl -s \"https://api.frankfurter.dev/v1/latest?base=USD&symbols=TRY\"", "r");
#else
        popen("curl -s \"https://api.frankfurter.dev/v1/latest?base=USD&symbols=TRY\"", "r");
#endif
    if (!fp) return fallback;

    char buffer[2048] = {0};

    // read the whole response (sometimes it won’t fit in one fgets)
    char temp[512];
    while (fgets(temp, sizeof(temp), fp)) {
        strncat(buffer, temp, sizeof(buffer) - strlen(buffer) - 1);
    }

#ifdef _WIN32
    _pclose(fp);
#else
    pclose(fp);
#endif

    float rate = fallback;
    char *p = strstr(buffer, "\"TRY\":");
    if (p) {
        // move past '"TRY":'
        p += 6;
        // skip spaces
        while (*p == ' ' || *p == '\t') p++;
        sscanf(p, "%f", &rate);
    }

    if (rate <= 0.0f) return fallback;
    return rate;
}
void clearLine(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}