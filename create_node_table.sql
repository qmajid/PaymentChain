-- Table: public.node

-- DROP TABLE public.node;

CREATE TABLE public.node
(
  node_id integer NOT NULL,
  node_node_name character varying(30),
  node_node_type integer,
  node_node_id integer,
  node_ip character varying(20),
  node_port integer,
  node_service_port integer,
  CONSTRAINT node_pkey PRIMARY KEY (node_id)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.node
  OWNER TO postgres;

