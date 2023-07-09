
#include "nvs_custom.h"

nvs_handle_t my_handle;

void NVS_open()
{
    esp_err_t err;
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        printf("Done\n");
    }
}

esp_err_t get_wifi_ssid(void)
{
    printf("get_wifi_ssid \n");
    NVS_open();

    esp_err_t err;

    // Read run time blob
    size_t required_size = 0; // value will default to 0, if not set yet in NVS
    // obtain required memory space to store blob being read from NVS
    err = nvs_get_blob(my_handle, "wifi_ssid", NULL, &required_size);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        return err;
    }
    if (required_size == 0)
    {
        printf("Nothing saved yet!\n");
    }
    else
    {
        char wifi_ssid[20];
        err = nvs_get_blob(my_handle, "wifi_ssid", wifi_ssid, &required_size);
        if (err != ESP_OK)
        {
            return err;
        }
        printf("WIFI SSID NVS = %s \n", wifi_ssid);
    }

    // Close
    nvs_close(my_handle);
    return ESP_OK;
}









esp_err_t set_nvs_key_value(char* key, char *key_value)
{
    NVS_open();
    printf("setting %s to value = %s\n",key,key_value);
    esp_err_t err;
    // Open
    err = nvs_set_blob(my_handle, key, key_value, strlen(key_value)+1 );
    if (err != ESP_OK)
    {
        return err;
    }

    // Commit
    err = nvs_commit(my_handle);
    if (err != ESP_OK)
    {
        return err;
    }
    // Close
    nvs_close(my_handle);
    return ESP_OK;
}


esp_err_t get_nvs_key_value(char* key, char* return_value)
{
    NVS_open();
    printf("Reading nvs key %s value \n",key);
    esp_err_t err;

    // Read run time blob
    size_t required_size = 0; // value will default to 0, if not set yet in NVS
    // obtain required memory space to store blob being read from NVS
    err = nvs_get_blob(my_handle, key, NULL, &required_size);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        return err;
    }
    if (required_size == 0)
    {
        printf("Nothing saved yet!\n");
    }
    else
    {
        char read_value[20];
        printf("get required size = %u \n",required_size);
        err = nvs_get_blob(my_handle, key, return_value, &required_size);
        if (err != ESP_OK)
        {
            return err;
        }
        printf("%s key value = %s \n", key,return_value);
        return_value = read_value;
    }

    // Close
    nvs_close(my_handle);
    return ESP_OK;
}

// esp_err_t save_wifi_ssid(char *new_wifi_ssid)
// {
//     printf("save_wifi_ssid \n");
//     NVS_open();
//     esp_err_t err;
//     // Open
//     printf("ssid length = %u\n", strlen(new_wifi_ssid));
//     err = nvs_set_blob(my_handle, "wifi_ssid", new_wifi_ssid, strlen(new_wifi_ssid) + 1);
//     if (err != ESP_OK)
//     {
//         return err;
//     }

//     // Commit
//     err = nvs_commit(my_handle);
//     if (err != ESP_OK)
//     {
//         return err;
//     }
//     // Close
//     nvs_close(my_handle);
//     return ESP_OK;
// }

// esp_err_t save_wifi_pass(char *new_wifi_pass)
// {
//     printf("save_wifi_pass \n");
//     NVS_open();
//     esp_err_t err;
//     // Open
//     printf("pass length  = %u\n", strlen(new_wifi_pass));
//     err = nvs_set_blob(my_handle, "wifi_pass", new_wifi_pass, strlen(new_wifi_pass) + 1);
//     if (err != ESP_OK)
//     {
//         return err;
//     }

//     // Commit
//     err = nvs_commit(my_handle);
//     if (err != ESP_OK)
//     {
//         return err;
//     }
//     // Close
//     nvs_close(my_handle);
//     return ESP_OK;
// }