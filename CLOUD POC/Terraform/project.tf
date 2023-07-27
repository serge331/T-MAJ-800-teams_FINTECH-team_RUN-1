data "ovh_order_cart" "mycart" {
ovh_subsidiary = "fr"
description    = "cloud order cart"
}

data "ovh_order_cart_product_plan" "plan" {
cart_id        = data.ovh_order_cart.mycart.id
price_capacity = "renew"
product        = "cloud"
plan_code      = "project"
}

resource "ovh_cloud_project" "project" {
ovh_subsidiary = data.ovh_order_cart.mycart.ovh_subsidiary
description    = "Projet_Kube_FINTECH"
payment_mean   = "default-payment-mean"

plan {
  duration     = data.ovh_order_cart_product_plan.plan.selected_price.0.duration
  plan_code    = data.ovh_order_cart_product_plan.plan.plan_code
  pricing_mode = data.ovh_order_cart_product_plan.plan.selected_price.0.pricing_mode
}
}