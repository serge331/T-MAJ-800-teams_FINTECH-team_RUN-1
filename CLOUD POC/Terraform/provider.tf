terraform {
  required_providers {
    ovh = {
      source = "ovh/ovh"
    }
  }
}

provider "ovh" {
  endpoint           = var.provider_endpoint
  application_key    = var.provider_application_key
  application_secret = var.provider_application_secret
  consumer_key       = var.provider_consumer_key
}