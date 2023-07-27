#variable provider
variable "provider_endpoint" {
  type    = string
  default = "ovh-eu"
}
variable "provider_application_key" {
  type = string
}
variable "provider_application_secret" {
  type = string
}
variable "provider_consumer_key" {
  type = string
}

#variable cluster
variable "cluster_project-id" {
  type = string
}
variable "cluster_id" {
  type    = string
  default = ""
}
variable "cluster_name" {
  type = string
}
variable "cluster_poolname" {
  type    = string
  default = ""
}
variable "cluster_region" {
  type = string
}
variable "cluster_version" {
  type = string
}
variable "cluster_autoscale" {
  type    = bool
  default = false
}
variable "cluster_type_vm" {
  type = string
}
variable "cluster_anti_affinity" {
  type    = bool
  default = false
}
variable "cluster_monthly_billed" {
  type    = bool
  default = false
}
variable "cluster_desired_nodes" {
  type = number
}
variable "cluster_max_nodes" {
  type    = number
  default = 5
}
variable "cluster_min_nodes" {
  type    = number
  default = 3
}
variable "cluster_ip_restriction" {
  type    = list
  default = []
}